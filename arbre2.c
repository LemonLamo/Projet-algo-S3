#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "include/raylib.h"
#include "include/raygui.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
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
    int n=randomvlue(0,4);
    int x=randomvlue(1,50);
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
        DrawCircle(posx,posy,20,a->col);
        DrawText(TextFormat("%d",a->info),posx-15,posy-10,25,BLACK);
       for(i=0;i<n;i++){
        if(a->A[i]!=NULL){
        if(i<=n/2){
            DrawLine(posx,posy+20,posx-100*(n/2-i),posy+100,BLACK);
            drawarbre(a->A[i],posx-100*(n/2-i),posy+100);
       }else{
           DrawLine(posx,posy+20,posx+(i-n/2)*100,posy+100,BLACK);
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
int main(){
    //arrow for revenir button 
    
    //adding blend mode for alpha values 
    BlendMode currentBlendMode = BLEND_ALPHA;
    // adding the color palette of the project 
    int colorPurple = 0x53405EFF;
    int colorRed = 0x90314FFF;
    int colorOrange = 0xDD704FFF;
    int colorYellow = 0xF6D0A1FF;
    int colorBlue = 0x5B8090FF;
    int textColorWhite = 0xF5F5F5FF;
    //adding background color 
    Color backgroundColor = { 230,217,241, 1 };
    // text size for buttons 
    int textSize = 36;

    Rectangle rec1={50,50,120,50};
    Rectangle rec2={50,150,120,50};
    Rectangle rec3={10,350,50,50};
    Rectangle rec4={110,350,50,50};
    Rectangle rec5={55,420,50,50};
    Rectangle rec6={50,250,135,50};
    Button CR=initbutton(rec1,"Creation",RED);
    Button re=initbutton(rec2,"Recherche",RED);
    Button sup=initbutton(rec6,"Suppression",RED);
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
    bool state[4]={false,false,false,false};
     arbre a=creat();
     int pos=0;
     int value=0;
    InitWindow(1400,500,"arbre");
    //initaliser l'application sur le premier ecran 
    Ecran ecranActuel = ECRAN_UN;
    Rectangle arbreRec = { 600, 200, 120, 50 };


    //pop-up logic 
    bool exitWindow = false;
    bool popupActive = false;
  
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
            DrawText("Are you sure you want to exit?", 520, 264, 20, BLACK);

            // Draw Yes button
            if (GuiButton((Rectangle){ 536, 292, 100, 50 }, "Yes"))
            {
                exitWindow = true;
            }

            // Draw No button
            if (GuiButton((Rectangle){ 732, 292, 100, 50 }, "No"))
            {
                popupActive = false;
            }

            EndDrawing();
        }else{
         BeginDrawing();
                    ClearBackground(backgroundColor);
                    currentBlendMode = BLEND_ALPHA;
                    BeginBlendMode(currentBlendMode);
                    
                    GuiSetStyle(BUTTON, BORDER_COLOR_NORMAL, colorRed);
                    GuiSetStyle(BUTTON, TEXT_COLOR_NORMAL, textColorWhite);
                    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, colorOrange);
                    GuiSetStyle(BUTTON, TEXT_SIZE, textSize);
                    switch(ecranActuel){
                        case ECRAN_UN: 
                            if (GuiButton(arbreRec, "Arbre N-aire")) {
                             ecranActuel = (ecranActuel == ECRAN_UN) ? ECRAN_DEUX : ECRAN_UN;
                                                                    }   
                            
                             // close the app 
                             if( GuiButton(sortirRec,"sortir")){
                                CloseWindow();
                             }
                            break;
                        case ECRAN_DEUX: 
                                drawButton(CR);
                                drawButton(re);
                                //drawButton(sup);
                                //drawButton(revenirBtn);
                    if(GuiButton(revenirRec,"revenir")){
                        ecranActuel = ECRAN_UN;
                    }
                    
                    if(buttonpressed(CR) ||state[0] ){
                        if(buttonpressed(CR)){
                            max1=0;
                            a=creat();
                            CR.col=BLUE;
                            re.col=RED;
                            sup.col=RED;
                        }
                    drawarbre(a,700,50);
                    state[0]=true;
                    }
                    if(state[1]||state[2]){
                        drawButton(left);
                        drawButton(right);
                        drawButton(ok);
                        
                        DrawText(TextFormat("%d",value),70,360,30,BLACK);
                        if(buttonpressed(right))
                            value++;
                        if(buttonpressed(left))
                            value--;
                    }
                    if(buttonpressed(re) ||state[1]){
                        if(buttonpressed(re)){
                          CR.col=RED;
                          re.col=BLUE;
                          sup.col=RED;  
                        }
                        state[1]=true;
                        state[2]=false;
                        if(buttonpressed(ok)&&state[1] ){ 
                        Recherche(a,value);
                        }
                        
                        
                    }
                    if(GuiButton(rec6,"suppression") ||state[2]){
                        if(GuiButton(rec6,"suppression")){
                         CR.col=RED;
                         re.col=RED;
                         sup.col=BLUE;   
                        }
                        state[2]=true;
                        state[1]=false;
                        if(buttonpressed(ok)&&state[2])
                            supp(&a,NULL,value);
                    }
                    break;
                    }
                   
                    EndBlendMode();
                    
                    EndDrawing();       
        }
                       
        
              
    }
}
        
