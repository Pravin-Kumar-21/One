//
// Created by Max on 9/4/2022.
//

#include "error.h"

// Global variable(s)
//extern Lexer lexer;

Error* error_init(ErrorType type, ErrorSubType subtype, char* message, char* source, Location start, Location end)
{
    Error* error = (Error*)malloc(sizeof(Error));
    error->type = type;
    error->subtype = subtype;
    error->message = message;
    error->source = source;
    error->start = start;
    error->end = end;

    return error;
}
/*
 * @function: error
 * @description: Occur a error/warning at the runtime, If that was not a warning so we will exit the program immediately
 * @arguments: ErrorType, int line, const char* file, const char* function, const char* format varg...
 * @return: void; nothing
 */
void error(ErrorType type, int line, const char* file, const char* function, const char* format, ...)
{
    debug("error");

    va_list args;
    va_start(args, format);
    // TODO: Show error type with another custom color!
    fprintf(stderr, "%s: ", error_name(type));
    vfprintf(stderr, format, args);
    va_end(args);

    // fprintf(stderr, "[at %s line %d in %s]", file, line, function);

//    Location loc;
    char* path = NULL;

//#ifdef _ONE_PARSER_
//    Token* current_token = (*parser.tokens);
//	loc = current_token->pos;
//	path = parser.path;
//#elif defined _ONE_LEXER_
//    loc = lexer.loc;
//#endif

    path = (path == NULL) ? "REPL" : path;
//    fprintf(stderr, " at %s:%zu:%zu", path, loc.line, loc.column);
    fprintf(stderr, " at %s", path);
    fputs("\n", stderr);

    if (type != ERROR_WARNING)
    {
        exit(1);
    }
}

/*
 * @function: error_name
 * @description: Convert a ErrorType value to char*, mapping to its name
 * @arguments: ErrorType
 * @return: char*
 */
char* error_name(ErrorType type)
{
    debug("error_name");

    switch (type)
    {
        case ERROR_TREE:
            return "TREE";
        case ERROR_WARNING:
            return "WARNING";
        case ERROR_PANIC:
            return "ERROR";
        case ERROR_TOKEN:
            return "TOKEN ERROR";
        case ERROR_PARSER:
            return "PARSER ERROR";
        default:
            return "UNKNOWN ERROR";
    }
}
