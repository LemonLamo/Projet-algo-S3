#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "raylib.h"
#include "raygui.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#undef RAYGUI_IMPLEMENTATION
typedef enum Ecran { ECRAN_UN, ECRAN_DEUX } Ecran;
typedef struct Button Button;
struct Button{
    Rectangle rec;
    char *text;
    Color col;
};
Button initbutton(Rectangle rec,char *t,Color col){
    Button b;
    b.rec=rec;
    b.text=t;
    b.col=col;
    return b;
}
void drawButton(Button b){
    DrawRectangleRec(b.rec,b.col);
    DrawText(b.text,b.rec.x+10,b.rec.y+10,20,BLACK);
    
}
bool buttonpressed(Button button){
    return (CheckCollisionPointRec(GetMousePosition(),button.rec) && IsMouseButtonPressed(0));
}
int randomvlue(int min,int max){
        
        int random=rand()%(max-min+1)+min;
        return random;
    }
typedef struct noued noued;
struct noued{
    int info;
    Color col;
    noued **A;
    int n;
};
typedef noued * arbre;
int max1=0;
arbre creat(){
    int n=randomvlue(1,4);
    int x=randomvlue(-100,100);
    arbre a;
    max1++;
    a=malloc(sizeof(noued));
    a->info=x;
    a->col=RED;
    a->n=n;
    if(n==0 || max1>=5){
        a->A=NULL;
         a->n=0;
    }else{
    a->A=malloc(n*sizeof(arbre));
    for(int i=0;i<n;i++){
       a->A[i]=creat();
    }
    }
  
    return a;
}

void drawarbre(arbre a,int posx,int posy){
    int i;
    if(a!=NULL){
        int n;
        n=a->n;
        DrawCircle(posx,posy,25,a->col);
        DrawText(TextFormat("%d",a->info),posx-15,posy-10,25,BLACK);
        
       for(i=0;i<n;i++){
        if(a->A[i]!=NULL){
        if(i<=n/2){
            
            DrawLine(posx,posy+20,posx-100*(n/2-i),posy+100,BLACK);
             Sleep(1);
            drawarbre(a->A[i],posx-100*(n/2-i),posy+100);
       }else{
           
           DrawLine(posx,posy+20,posx+(i-n/2)*100,posy+100,BLACK);
            Sleep(1);
           drawarbre(a->A[i],posx+(i-n/2)*100,posy+100);
    
       }
        }
       
        
    }
   }
}
void Recherche(arbre a,int val){
    if(a!=NULL){
        if(a->info==val)
            a->col=GREEN;
        else{
            a->col=RED;
        }
            for(int i=0;i<a->n;i++){
                Recherche(a->A[i],val);
            }
        
    }
}
int feuil(arbre *a,arbre pere){
    int x;
    if((*a)->n==0){
        x=(*a)->info;
        if(pere==NULL){
           *a=NULL;
        }else{           
        for(int i=0;i<pere->n;i++){
            if(pere->A[i]==*a){
                pere->A[i]=NULL;
                for(int j=i;j<pere->n-1;j++){
                    pere->A[j]=pere->A[j+1];
                }
                pere->n=pere->n-1;
            }            
        }
        free(*a);
        }
        return x;
     }else{
         for(int i=0;i<(*a)->n;i++){
             if((*a)->A[i]!=NULL){
               return feuil(&(*a)->A[i],*a);
             }
         }
     }
}
void supp(arbre *a,arbre pere,int val){
    if(*a!=NULL){
        (*a)->col=RED;
        if((*a)->info==val){
            (*a)->info=feuil(a,pere);
        }else{
            for(int i=0;i<(*a)->n;i++){
                supp(&(*a)->A[i],*a,val);
            }
        }
    }
}
void minimum(arbre a,int *min){
    if(a!=NULL){
        if(a->info<*min)
            *min=a->info;
        if(a->n!=0){
           for(int i=0;i<a->n;i++){
             minimum(a->A[i],min);
            }
            }  
        }
    }
void maximum(arbre a,int *max){
    if(a!=NULL){
        if(a->info>*max)
            *max=a->info;
        if(a->n!=0){
           for(int i=0;i<a->n;i++){
             maximum(a->A[i],max);
            }
            }  
        }
   }
//int index = 0;
int getSize(arbre root) {
    if (root == NULL) return 0;

    int size = 1; // Count the root

    for (int i = 0; i < root->n; i++) {
        size += getSize(root->A[i]); // Recursively count the size of subtrees
    }

    return size;
}
int compare(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}
int compareDesc(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_b > int_a) - (int_b < int_a);
}
void storeNodes(arbre root, int* array, int* index) {
    if (root == NULL) return;

    for (int i = 0; i < root->n; i++) {
        storeNodes(root->A[i], array, index);
    }

    array[(*index)++] = root->info;
}
void putNodesBack(arbre root, int* array, int* index) {
    if (root == NULL) return;

    for (int i = 0; i < root->n; i++) {
        putNodesBack(root->A[i], array, index);
    }

    root->info = array[(*index)++];
}
void sortArrayDesc(int* array, int size) {
    qsort(array, size, sizeof(int), compareDesc);
}
void sortTree(arbre root) {
    int size = getSize(root);
    int* array = malloc(size * sizeof(int));
    int index = 0;

    storeNodes(root, array, &index);

    qsort(array, size, sizeof(int), compare);

    index = 0;
    putNodesBack(root, array, &index);

    free(array);
}
void sortTreeDesc(arbre root) {
    int size = getSize(root);
    int* array = malloc(size * sizeof(int));
    int index = 0;

    storeNodes(root, array, &index);

    sortArrayDesc(array, size);

    index = 0;
    putNodesBack(root, array, &index);

    free(array);
}
int main(){
    // Dropdown box items
    const char *items = "1-ASC;2-DSC"; 
    int activeItem = 0;
    int  selectedItem = -1;
    //adding blend mode for alpha values 
    BlendMode currentBlendMode = BLEND_ALPHA;
    // adding the color palette of the project 
    int colorPurple = 0x53405EFF;
    int colorRed = 0x90314FFF;
    int colorOrange = 0xDD704FFF;
    int colorYellow = 0xF6D0A1FF;
    int colorBlue = 0x5B8090FF;
    int textColorWhite = 0xF5F5F5FF;
    int colorEcarlate = 0xE71A3AFF;
    int colorJade = 0x009E69FF;
    int colorPetrol = 0x060173FF;
    //adding background color 
    Color backgroundColor = { 230,217,241, 1 };
    // text size for buttons 
    int textSize = 36;
    int min1;
    int max2;
    Rectangle rec1={50,10,135,50};
    Rectangle rec2={50,70,135,50};
    Rectangle rec3={10,350,50,50};
    Rectangle rec4={110,350,50,50};
    Rectangle rec5={55,420,50,50};
    // for search 
    Rectangle recSearch = {55,350,50,50};
    Rectangle rec6={50,130,135,50};
    Rectangle rec7={50,200,50,50};
    Rectangle rec8={50,270,50,50};
    Button CR=initbutton(rec1,"Creation",RED);
    Button re=initbutton(rec2,"Recherche",RED);
    Button sup=initbutton(rec6,"Suppression",RED);
    Button min=initbutton(rec7,"min",ORANGE);
    Button max=initbutton(rec8,"max",ORANGE);
    Button left=initbutton(rec3,"<",GREEN);
    Button right=initbutton(rec4,">",GREEN);
    Button ok=initbutton(rec5,"OK",GREEN);
    //les boutons du 1er ecran 
    //Rectangle voirArbreRec = {50,50,120,50};
    Rectangle sortirRec = {600,264,120,50};
    
    Rectangle revenirRec = {1280,0,120,50};
   //Button voirArbreBtn = initbutton(voirArbreRec,"Voir arbre",LIGHTGRAY);
    Button sortirBtn = initbutton(sortirRec,"sortir",LIGHTGRAY);
    Button revenirBtn = initbutton(revenirRec,"revenir",LIGHTGRAY);
    srand(time(NULL));
    bool state[5]={false,false,false,false,false};
     arbre a=creat();
     int value=0;
    InitWindow(1400,500,"arbre");
    //initaliser l'application sur le premier ecran 
    Ecran ecranActuel = ECRAN_UN;
    Rectangle arbreRec = { 600, 200, 120, 50 };
    Rectangle welcomeRec = { 400, 50, 500, 50 };
    Rectangle hintRec = { 264, 114, 800, 50 };
    //pop-up logic 
    bool exitWindow = false;
    bool popupActive = false;

    //for search input 
    char numStrSearch[32] = "\0";
    int numberSearch = 0;
    // for delete input 
    char numStrDelete[32] = "\0";
    int numberDelete = 0;
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18); // Set global style default font size
    //GuiSetStyle(TEXTBOX, TEXT_SIZE, 20); // Set specific control property

    Font font = GetFontDefault(); // Get the default font
    Vector2 position = {10, 10}; // Position for the text
    float fontSize = 20.0; // Font size
    float spacing = 1.0; // Spacing for the text
    Color color = BLACK; // Color of the text
    SetTargetFPS(60);
    while(!exitWindow){
           /* if (GuiButton(arbreRec, "Voir arbre")) {
            ecranActuel = (ecranActuel == ECRAN_UN) ? ECRAN_DEUX : ECRAN_UN;
        }   */
        if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE))
        {
            popupActive = true;
        }
        if (popupActive)
        {
            // Draw the popup
            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawRectangle(500, 200, 364, 200, GRAY);
            DrawText("Etes-vous sûr de vouloir quitter?", 520, 264, 20, BLACK);

            // Draw Yes button
            if (GuiButton((Rectangle){ 536, 292, 100, 50 }, "Oui"))
            {
                exitWindow = true;
            }

            // Draw No button
            if (GuiButton((Rectangle){ 732, 292, 100, 50 }, "Non"))
            {
                popupActive = false;
            }

            EndDrawing();
        }else{
         BeginDrawing();
                    ClearBackground(backgroundColor);
                    
                    
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, colorRed);
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorOrange);
                    GuiSetStyle(BUTTON, TEXT_SIZE, 25);
                    switch(ecranActuel){
                        case ECRAN_UN: 
                        GuiSetStyle(DEFAULT, TEXT_SIZE, 25);
                        GuiSetStyle(LABEL, TEXT_COLOR_NORMAL, colorBlue);
                        GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
                        GuiLabel(welcomeRec,"Bienvenue sur notre Projet !");
                        GuiSetStyle(DEFAULT, TEXT_SIZE, 22);
                        GuiLabel(hintRec,"Cliquez sur Arbre N-aire pour en manipuler un");
                        GuiSetStyle(DEFAULT, TEXT_SIZE, 18);
                        DrawText("Projet fait par :", 1200, 350, 20, GetColor(colorPetrol));

                        DrawText("- Lamia Koucem", 1200, 380, 20, GetColor(colorPurple));
                        DrawText("- Amine Selatna", 1200, 410, 20, GetColor(colorPurple));
                        DrawText("- Wail Mansour", 1200, 440, 20, GetColor(colorPurple));

                            if (GuiButton(arbreRec, "Arbre N-aire")) {
                             ecranActuel = (ecranActuel == ECRAN_UN) ? ECRAN_DEUX : ECRAN_UN;
                                                                    }   
                            
                             // close the app 
                             if( GuiButton(sortirRec,"sortir")){
                                CloseWindow();
                             }
                            break;
                        case ECRAN_DEUX: 
                                //drawButton(CR);
                                //drawButton(re);

                                //drawButton(min);
                                //drawButton(max);
                                //drawButton(sup);
                                //drawButton(revenirBtn);
                    if(GuiButton(revenirRec,"revenir")){
                        ecranActuel = ECRAN_UN;
                    }
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x000000AA);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorJade);
                    GuiSetStyle(BUTTON, TEXT_SIZE, 25);
                    GuiDrawText("1-ASC : Trier les noeuds du plus petit au plus grand",(Rectangle){ 950, 100, 450, 40 },TEXT_ALIGN_LEFT, BLACK);
                    GuiDrawText("2-DSC : Trier les noeuds du plus grand au plus petit",(Rectangle){ 950, 164, 450, 40 },TEXT_ALIGN_LEFT, BLACK);
                    GuiComboBox((Rectangle){ 1100, 250, 120, 40 }, items, &activeItem);
                    
                    
                    if (GuiButton((Rectangle){ 1100, 314, 120, 40 }, "Trier")) {
                            if(activeItem == 1){
                                    sortTree(a);
                                    drawarbre(a,750,50);
                                }else{
                                    sortTreeDesc(a);
                                    
                                    drawarbre(a,750,50);
                                }
                    }
                    if(GuiButton(rec1,"Création") ||state[0] ){
                        if(GuiButton(rec1,"Création")){
                            max1=0;
                            state[3]=false;
                            state[4]=false;
                            a=creat();
                            CR.col=BLUE;
                            re.col=RED;
                            sup.col=RED;
                        }
                    drawarbre(a,750,50);
                    state[0]=true;
                    }
                    if(state[1]||state[2]){
                        //drawButton(left);
                        //drawButton(right);
                        drawButton(ok);
                        
                        //DrawText(TextFormat("%d",value),70,360,30,BLACK);
                        /* if(buttonpressed(right))
                            value++;
                        if(buttonpressed(left))
                            value--;*/
                    }
                     GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x000000AA);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorPetrol);
                    GuiSetStyle(BUTTON, TEXT_SIZE, 25);
                    if(GuiButton(rec2,"Recherche") ||state[1]){
                        if(GuiButton(rec2,"Recherche")){
                          CR.col=RED;
                          re.col=BLUE;
                          sup.col=RED;  
                        }
                        state[1]=true;
                        state[2]=false;
                        GuiLabel((Rectangle){15,315,300,50},"Entrez une valeur a rechercher");
                        GuiTextBox(recSearch,numStrSearch,32,true);
                        if(buttonpressed(ok)&&state[1] ){ 
                            numberSearch = atoi(numStrSearch);
                            Recherche(a,numberSearch);
                        }
                        
                        
                    }
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x000000AA);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorEcarlate);
                    GuiSetStyle(BUTTON, TEXT_SIZE, 25);
                    if(GuiButton(rec6,"suppression") ||state[2]){
                        if(GuiButton(rec6,"suppression")){
                         CR.col=RED;
                         re.col=RED;
                         sup.col=BLUE;   
                        }
                        state[2]=true;
                        state[1]=false;
                        GuiLabel((Rectangle){15,315,300,50},"Entrez une valeur a supprimer");
                        GuiTextBox(recSearch,numStrDelete,32,true);
                        if(buttonpressed(ok)&&state[2]){
                            numberDelete = atoi(numStrDelete);
                            supp(&a,NULL,numberDelete);
                        }
                            
                    }
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorBlue);
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x000000AA);
                    if(GuiButton(rec7,"Min")||state[3]){
                        state[3]=true;
                        min1=100;
                        minimum(a,&min1);
                        DrawText(TextFormat("%d",min1),110,205,40,BLACK);
                        sortTree(a);
                        drawarbre(a,750,50);
                    }
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorRed);
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, 0x000000AA);
                    if(GuiButton(rec8,"Max")||state[4]){
                        state[4]=true;
                        max2=-100;
                        maximum(a,&max2);
                        DrawText(TextFormat("%d",max2),110,275,40,BLACK);
                    }
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorOrange);
                    break;
                    }
                   
                    
                    //free(a);
                    EndDrawing();       
        }
                       
        
              
    }
}
        