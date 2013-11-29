#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <stdarg.h>
#include <unordered_map>
#include <stdexcept>
#include <unistd.h>

typedef std::vector<uint32_t> physical_memory_t;
typedef std::unordered_map<uint32_t, physical_memory_t> virtual_memory_t;

struct Opcode1
{
    uint32_t c:3;
    uint32_t b:3;
    uint32_t a:3;
    uint32_t dummy:19;
    uint32_t code:4;
};

struct Opcode2
{
    uint32_t value:25;
    uint32_t a:3;
    uint32_t code:4;
};

class VirtualMachine
{
public:
    VirtualMachine(const physical_memory_t &program, FILE *inputFile, FILE *outputFile);

    void Run();

private:
    void ConditionalMove();
    void ArrayIndex();
    void ArrayAmendment();
    void Addition();
    void Multiplication();
    void Division();
    void NotAnd();
    void Allocation();
    void Abandonment();
    void Output();
    void Input();
    void LoadProgram();
    void Orthography();

    uint32_t registers[8];
    physical_memory_t program;
    uint32_t *executionPoint;
    Opcode1 *o1;
    Opcode2 *o2;
    virtual_memory_t memory;
    uint32_t memoryPageIndex;
    FILE *outputFile;
    FILE *inputFile;
};

VirtualMachine::VirtualMachine(const physical_memory_t &_program, FILE *_inputFile, FILE *_outputFile)
    : program(_program), inputFile(_inputFile), outputFile(_outputFile)
{
    std::fill(std::begin(registers), std::end(registers), 0);
    executionPoint = program.data();
    memoryPageIndex = 1;
}

void VirtualMachine::Run()
{
    for(bool execution = true; execution; )
    {
        o1 = (Opcode1 *)executionPoint;
        o2 = (Opcode2 *)executionPoint;
#if 0
        printf("%08X: %08X %2d(%2d) %u ", executionPoint - program.data(), *executionPoint, o1->code, o2->code, memoryPageIndex);
        if (o1->code == 13)
            printf("{ %d, %08X } ", o2->a, o2->value);
        else
            printf("{ %d, %d, %d     } ", o1->a, o1->b, o1->c);
        printf("{");
        for(int i = 0; i != 8; ++i)
            printf(" %d:%08X", i, registers[i]);
        printf(" }\n");
#endif
        ++executionPoint;

        switch(o1->code)
        {
        case 0:
            ConditionalMove();
            break;
        case 1:
            ArrayIndex();
            break;
        case 2:
            ArrayAmendment();
            break;
        case 3:
            Addition();
            break;
        case 4:
            Multiplication();
            break;
        case 5:
            Division();
            break;
        case 6:
            NotAnd();
            break;
        case 7:
            execution = false;
            break;
        case 8:
            Allocation();
            break;
        case 9:
            Abandonment();
            break;
        case 10:
            Output();
            break;
        case 11:
            Input();
            break;
        case 12:
            LoadProgram();
            break;
        case 13:
            Orthography();
            break;
        }
    }
}

void ThrowRuntimeError(char const *format, ...)
{
    char message[1000];

    va_list args;
    va_start(args, format);
    vsprintf(message, format, args);
    va_end(args);

    throw std::runtime_error(message);
}

void VirtualMachine::ConditionalMove()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    if (C)
        A = B;
}

void VirtualMachine::ArrayIndex()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    if (!B)
    {
        if (program.size() <= C)
            ThrowRuntimeError("ArrayIndex: invalid array offset. array: %d, size: %u, offset: %d", B, program.size(), C);
        A = program[C];
        return;
    }

    auto i = memory.find(B);
    if (i == memory.end())
        ThrowRuntimeError("ArrayIndex: invalid array index. array: %d", B);
    physical_memory_t &page = i->second;
    if (page.size() <= C)
        ThrowRuntimeError("ArrayIndex: invalid array offet. array: %d, size: %u, offset: %d", B, page.size(), C);

    A = page[C];
}

void VirtualMachine::ArrayAmendment()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    if (!A)
    {
        if (program.size() <= B)
            ThrowRuntimeError("ArrayAmendment: invalid array offset. array: %d, size: %u, offset: %d", A, program.size(), B);
        program[B] = C;
        return;
    }

    auto i = memory.find(A);
    if (i == memory.end())
        ThrowRuntimeError("ArrayAmendment: invalid array index. array: %d", A);
    physical_memory_t &page = i->second;
    if (page.size() <= B)
        ThrowRuntimeError("ArrayAmendment: invalid array offset. array: %d, size: %u, offset: %d", A, page.size(), B);

    page[B] = C;
}

void VirtualMachine::Addition()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    A = B + C;
}

void VirtualMachine::Multiplication()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    A = B * C;
}

void VirtualMachine::Division()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    A = B / C;
}

void VirtualMachine::NotAnd()
{
    uint32_t &A = registers[o1->a];
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    A = ~(B & C);
}

void VirtualMachine::Allocation()
{
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    memory[memoryPageIndex].resize(C);
    B = memoryPageIndex;

    ++memoryPageIndex;
}

void VirtualMachine::Abandonment()
{
    uint32_t &C = registers[o1->c];

    if (!C)
        ThrowRuntimeError("Abandonment: invalid array index. array: %d", C);
    auto i = memory.find(C);
    if (i == memory.end())
        ThrowRuntimeError("Abandonment: unknown array index. array: %d", C);

    memory.erase(i);
}

void VirtualMachine::Output()
{
    uint32_t &C = registers[o1->c];

    fputc(C, outputFile);
}

void VirtualMachine::Input()
{
    uint32_t &C = registers[o1->c];

    C = fgetc(inputFile);
}

void VirtualMachine::LoadProgram()
{
    uint32_t &B = registers[o1->b];
    uint32_t &C = registers[o1->c];

    if (B)
    {
        auto i = memory.find(B);
        if (i == memory.end())
            ThrowRuntimeError("LoadProgram: invalid array index. array: %d", B);

        program = i->second;
    }
    executionPoint = program.data() + C;
}

void VirtualMachine::Orthography()
{
    uint32_t &A = registers[o2->a];

    A = o2->value;
}

void GetProgramFromFile(char const *path, physical_memory_t &program)
{
    std::vector<uint8_t> script;
    FILE *file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    script.resize(size);
    fread(script.data(), 1, size, file);
    fclose(file);

    if (size % 4)
        ThrowRuntimeError("invalid program size (%ld)", size);

    program.resize(size / 4);
    for(long i = 0, n = script.size(), j = 0; i != n; i += 4, ++j)
    {
        uint8_t A = script[i];
        uint8_t B = script[i + 1];
        uint8_t C = script[i + 2];
        uint8_t D = script[i + 3];

        program[j] = (((((A << 8) + B) << 8) + C) << 8) + D;
    }
}

void Usage()
{
    printf("arguments");
}

int main(int argc, char *argv[])
{
    std::string sourceFilePath;
    std::string inputFilePath;
    std::string outputFilePath;

    for(int c; (c = getopt(argc, argv, "i:o:s:")) != EOF; )
    {
        switch(c)
        {
        case 'i':
            inputFilePath = optarg;
            break;
        case 'o':
            outputFilePath = optarg;
            break;
        case 's':
            sourceFilePath = optarg;
            break;
        default:
            Usage();
            return 1;
        }
    }

    FILE *inputFile;
    FILE *outputFile;

    if (inputFilePath.empty())
        inputFile = stdin;
    else
        inputFile = fopen(inputFilePath.c_str(), "rt");
    if (outputFilePath.empty())
        outputFile = stdout;
    else
        outputFile = fopen(outputFilePath.c_str(), "wb");

    physical_memory_t program;
    GetProgramFromFile(sourceFilePath.c_str(), program);

    VirtualMachine vm(program, inputFile, outputFile);
    vm.Run();

    if (outputFile != stdout)
        fclose(outputFile);
    if (inputFile != stdin)
        fclose(inputFile);

    return 0;
}
