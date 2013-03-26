# Debugger

Possiblité d'afficher ça dans une console, 
ou de l'envoyer à travers un pipe, ou autre ?

assembler en mode debug pour avoir les symboles ?

réfléchir à une architecture extensible, qui permette même l'ajout de 
commandes personnalisées ?


possiblité de tracer des valeurs ou des adresses ? 
===>  à chaque arrêt, afficher le contenu

c.f. gdb
1. aliases
2. breakpoints
3. data
4. files
5. internals
6. obscure 
7. running
8. stack
9. status 
10. support
11. tracepoints
12. user-defined

## alias d'autres instructions
-> non

## breakpoints

- break line : placer un breakpoint à la ligne line (si macro instruction, à la première instruction correspondante)
- breakpoint label : arrêt quand arrivée sur l'adresse pointée par le label
- breakrange adresse : arrêt quand arrivée sur l'adresse
- breakpoint adresse offset : 
	arrêt quand arrivée dans l'intervalle [ adresse, adresse + offset]
- catch instruction : arrêt à chaque fois qu'on atteint une instruction de ce type
- watch port : arrêt si envoie d'une donnée sur le port spécifié. Affichage 
	de la valeur
- watch port in val : arrêt si lecture de val sur le port spécifié
- watfch port out val : arrêt si envoi de val sur le port spécifié
- unwatch port : 
- clear truc où truc est comme les arguments de break : efface le breakpoint
- uncatch instruction
- commands file : charge un fichier avec des commandes pour le débugger, à exécuter quand un breakpoint est atteint ou une instruction "catchée"


## data

- call function : appelle une fonction du programme
- display register : affiche la valeur d'une registre
- display adresse : affiche la valeur à l'adresse (affichage en hexadécimal)
- display adresse offset : affiche les valeurs aux adresse mémoire 
	de [ adresse, adresse + offset ]
- dump adresse offset fichier : idem qu'avant, mais enregistre en plus dans fichier
- dump : enregistre la valeur de tous les registres dans un fichier
- find sequences d'octets : recherche dans la mémoire une séquence d'octets,
	renvoie la première occurence
- find-next : recherche l'occurence suivante
- print texte : affiche le texte en argument
- write adresse val : écrire à l'adresse spécifiée la valeur val
- write adresse offset val : écrire dans la région [adresse, adresse + offset] la
	valeur val
- write register val : écrire dans le registre register la valeur val
- out port val : envoie la valeur val sur le port spécifié
- in port : lis le port spcifié

## files

- file fichier (ou file codeObjet codeAssembleur si les symboles ne sont pas dans le
	 fichier objet) : charge le fichier pour le débuggage
- path chemin : ajout du chemin au path

## internals
ras pour l'instant

##
- compare adresse offset fichier : compare le dump conservé dans fichier avec 
le contenu de la mémoire [adresse, adresse + offset]
- compare fichier : compare le dump des registres avec les valeurs de registre courant
- record : sauvegarde l'état de la machine 
- record fichier : sauvegarde l'état de la machine dans un fichier
- restore : restaure l'état de la machine  
- restore fichier : restaure l'état de la machine à partir du fichier
- stop : arrêt du débuggage


## running 
- continue : continue l'exécution
- c : continue l'exécution
- ctrl + c : met en pause l'exécution du programme 
- jump line 
- jump adresse
- jump label : saute à l'instruction référée par la ligne, le label, ou l'adresse (?)
- kill : stoppe définitivement le programme en cours de débuggage
- next : instruction suivante
- n : instruction suivante
- next n : avance de n lignes
- nextMacro : macro-instruction suivante (équivalent de step ?)
- nM : macro-instruction suivante
- reverse : instruction précédente (faire une mémoire de seulement les 100 ou 1000
	 ou alors choisis par l'utilisateur instructions précédentes)
- reverse n
- r : instruction précédente
- run : lance l'exécution du dernier programme chargé
- run file : lance l'exécution du fichier
- until : exécution jusqu'à ce que le programme avance dans les instructions
	(pratique pour sauter une boucle : on s'arrête au moment du saut, on met until, 
	et le programme s'arrêtera au sortir de la boucle)


## stack : inspection de la pile matérielle, et de la pile pointée par R31
- show stack n : affichage du contenu de la mémoire sur n octets à partir de l'adresse (faire une détection automatique de la pile d'appel ?)
de début de pile
- show callstack : afficher le contenu de la pile d'appel
- ret : retourne immédiatement de l'appel (simule un ret)


## status (peut-être changer les noms des watchpoints etc pour être consistant 
	avec gdb ?)
- info breakpoints : infos sur les breakpoints
- info watchpoints : infos sur les points de surveillance des I/O
- info catchpoints : c.f. avant
- info files : affiche les fichiers chargés
- info time : temps depuis le début de l'exécution du programme 
(sans compter les arrêts)

d'autres infos ? certainement !

## support 
- ! commande : exécute une commande shell
- help : affiche l'aide
- h : idem
- help commande ou h commande : affiche l'aide d'une commande
- source fichier : exécute les commandes de débuggage présentes dans le fichier

Ajout de if et de while ?
if end if else


Sans doute.

## tracepoints

## timing

Ajout de timing : pour mesurer la durée d'exécution

- time start : lancer le chronomètre
- time stop : arrêter le chronomètre
