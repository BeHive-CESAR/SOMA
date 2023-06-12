typedef struct {
    char email[50];
    char senha[15];
    unsigned int idCargo;
    unsigned int idResidencia;

} Usuario;


int cadastrar(int);
int login();

void def_usuario_logado(Usuario auth);