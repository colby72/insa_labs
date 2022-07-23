# Rendu: Ramy CHEMAK

###### Notes de cours ######
Un scan des notes de cours

###### Codes sources ######

## rk_detector.c
Détecteur de RootKit en comparant 2 listes de processus
--> (BUG) fonctionnel
--> Le détécteur fonctonnait bien au départ, en bien affichant les 2 listes. Au bout d'un nombre d'exécution pour une raison inconnue, il n'affiche plus la 1ère liste. La 1ère liste s'affichait pourtant bien au départ. Le programme reste fonctionnel tout de même.
--> Ce bug n'a pas géné la suite du TP, notamment la partie hook_calc_bf. Vu qu'on voulait cacher la calculatrice de la 2ème liste, rk_detector permettait bien de faire les tests nécessaires pour vérifier le fonctionnement du "hook".

## driver.c
RootKit rélaisant le delink du processus "calc.exe" dans le liste des EPROCESS
--> (OK) fonctionnel

## hook.c
Hook de NtCreateFile
--> (OK) fonctionnel

## hook_calc_bf.c
Hook de NtOpenProcess afin de cacher la calculatrice de la 2éme liste de rk_detector.c
--> (OK) fonctionnel

## hook_hide_file.c
Hook de ZwQueryDirectoryFile afin de cacher le ficher "virus.txt" dans "explorer.exe"
Le fichier reste bien visible si on fait un DIR dans CMD
--> (OK) fonctionnel
