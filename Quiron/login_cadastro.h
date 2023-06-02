typedef struct {
    char email[50];
    char senha[15];
    unsigned int idCargo;
} Usuario;


int cadastrar();
int login();
