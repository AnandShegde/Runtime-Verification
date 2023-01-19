const char EMPTY_NODE = '~';


enum types {unary, binary, operands, empty};

types get_type(char ch){
    switch (ch)
    {
        case '^':
        case 'v':
        case '>':
            return binary;

        case '!':
            return unary;

        case '~':
            return empty;

        default:
            return operands;
    }
}

int get_precendence(char ch){
    switch (ch)
    {
        case '!': return 100;
        case '^': return 99;
        case 'v': return 98;
        case '>': return 97;
    }
}