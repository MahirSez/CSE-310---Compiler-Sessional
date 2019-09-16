

%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%

[a-zA-Z]+ { words++ ; chars += strlen(yytext);}
\n        { chars++; lines++ ;}
.         { chars++; }

%%


int main(int argc ,char **argv) {

    if(argc != 2) {
        printf("Error!!");
        return 0;
    }

}
