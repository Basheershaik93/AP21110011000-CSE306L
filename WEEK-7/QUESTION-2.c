                    } else {
                        error();
                    }
                    break;

                case 'T' - 1:
                    if (ip[i] == '*') {
                        printf("\nT' -> *FT'");
                        pop();
                        push('T');
                        push('\'');
                        push('F');
                        push('*');
                    } else if (ip[i] == '+' || ip[i] == ')' || ip[i] == '$') {
                        printf("\nT' -> epsilon");
                        pop();
                    } else {
                        error();
                    }
                    break;

                case 'F':
                    if (ip[i] == 'd') {
                        printf("\nF -> d");
                        pop();
                        push('d');
                    } else if (ip[i] == '(') {
                        printf("\nF -> (E)");
                        pop();
                        push(')');
                        push('E');
                        push('(');
                    } else {
                        error();
                    }
                    break;

                default:
                    error();
            }
        }
    }
    return 0;
}
