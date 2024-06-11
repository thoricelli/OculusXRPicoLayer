typedef enum CallFrequency_ {
    NORMAL,
    FREQUENT
} CallFrequency;

typedef enum LogFunctionType_ {
    NON_IMPLEMENTED, //A function that is empty.
    IMPLEMENTED //A function that is already fully implemented
} LogFunctionType;

void LogFunction(LogFunctionType type, CallFrequency frequency, const char func[]);