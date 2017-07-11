struct Aeroporto
{
    struct pista *pis;
    int faltaCombust;
    int aviaoCaiu;
};
typedef struct Aeroporto aeroporto;

struct pista
{
    struct filadecola *dec;
    struct filapousa *pou;
    int ocupada;
};
typedef struct pista pis;

struct filadecola
{
    struct Aviao *ini;
    struct Aviao *fim;
    int cont;
};
typedef struct filadecola decola;

struct filapousa
{
    struct Aviao *ini;
    struct Aviao *fim;
    int cont;
};
typedef struct filapousa pousa;

struct Aviao
{
    int id;
    int combustivel;
    struct Aviao *prox;

};
typedef struct Aviao aviao;

aeroporto* cria();

void inPou(aeroporto *aero);

int caiu(aeroporto *aero);

int aviaoPousa(aeroporto *aero);

void inDec(aeroporto *aero);

int aviaoDecola(aeroporto *aero,int i);

int semCombustivel(aeroporto *aero);

void perdeCombustivel(aeroporto *aero);

void controlaAcoes(aeroporto *aero);

