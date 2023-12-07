
typedef struct
{
  
   int espAdmin;

} auth;


int ajouterAuth(char * filename, auth a );
int verifyAuth(char username[],char password[]);

int verifyAdmin(char filename[]);
