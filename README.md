# Bienvenu sur notre Projet de TP ASD3

## Thème 

Visualisation d'arbre N-aire en C 
##Trinôme 

- Lamia Koucem
- Amine Selatna
- Wail Mansour
  
## Description
Notre projet consiste a réaliser une interface de visualisation des arbres N-aire en utilisant le langage C. L'objectif est de créer une interface qui suit les concepts d'interface homme machine et offre une expérience utilisateur UX qui permet la bonne utilisation des fonctionnalités définies.

## Choix technologiques 
### Raylib
**Raylib** est une bibliothèque logicielle multiplateforme, écrite en C. Elle est orientée vers le développement d’applications interactives, telles que les jeux. Raylib est une bibliothèque hautement modulaire. Tout est contenu dans un petit nombre de modules bien définis, spécifiques et autonomes, nommés en fonction de leur fonctionnalité principale. Elle peut utiliser les bibliothèques OpenGL jusqu’à 3.3, GL ES 2.0 pour l’accélération matérielle. Elle se base en partie sur le framework GLFW.
### Raygui
**Raygui** est une bibliothèque simple et facile à utiliser pour la création d’interfaces utilisateur en mode immédiat. Elle a été initialement inspirée par Unity IMGUI (API GUI en mode immédiat) et a été créée comme un module auxiliaire pour Raylib pour créer des interfaces GUI simples en utilisant le style graphique de Raylib (couleurs simples, formes rectangulaires simples, larges bordures…). Raygui est destiné au développement d’outils (Toolbox).

Nous avons utilisé Raylib pour définir l'aspect graphique de l'arbre et Raygui pour redéfinir les boutons et champs en tout genre. 

## Démonstration 
Vous pouvez exécuter project.exe pour voir la dernière version du projet
### Ecran 1 : 
L'écran 1 contient : 
- Un bouton pour accéder au l'interface de visualisation et un autre pour sortir de l'application.
  
![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/6fd6711c-0369-4eed-a879-b558123bd13c)

- Si l'utilisateur décide de fermer la fenêtre de manière préemptive en cliquant en utilisant la touche ESC ou en fermant la fenêtre, une fenêtre jaillissante (Pop-up) apparaîtra pour confirmer si ceci est l'action voulue. Ce mécanisme permet d'éviter d'interrompre l'utilisation par erreur.

![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/a2c4b74f-2751-4ed4-bab5-2b5f4bf958ae)

### Ecran 2 : 
L'écran 2 contient les options suivantes : 

#### 1) Création 
Lorsque l'utilisateur clique sur Création , un arbre N-aire est crée 
![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/72e52312-4ae6-4144-9a4d-3389b5e551a1)

#### 2) Recherche 

Lorsque l'utilisateur clique sur le bouton recherche , un champ de saisie apparaît où il peut saisir une valeur a rechercher dans l'arbre. 
- Dans le cas où la valeur est présente dans l'arbre , le nœud en question change de couleur au vert au lieu de rouge pour indiquer a l'utilisateur où le nœud est. 
![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/8b7c3dd7-0fd2-4a76-aa92-f987c4cb82e1)

#### 3) Suppression 

Le bouton suppression, permet de supprimer un nœud de l'arbre et de le mettre a jour graphiquement. 
![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/75e4bcac-d929-4357-9664-82aaf8316bda)
![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/2eeb8326-9cb4-46b0-a562-69e54526a904)

#### 4) Min & Max 

Les boutons Min et Max permettent d'afficher la valeur minimale et maximale de l'arbre n-aire respectivement. 

#### 5) Trier 

Le bouton trier va faire en sorte de trier l'arbre en ordre descendant ( DSC ) ou ascendant (ASC) selon l'option choisie dans la boite de sélection. 

![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/b7a5d2a7-7d96-420c-82ec-4400bdafeaac)

![image](https://github.com/LemonLamo/Projet-algo-S3/assets/94323231/7b941122-a0d3-4a5c-9d13-6e31322abc0b)


