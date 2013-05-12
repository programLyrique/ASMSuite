# Debugger

1. breakpoints
3. data
4. files 
7. running
8. stack
9. status 
10. support
11. timing

## breakpoints

`breakpoint type arguments`

###Type : 
- `line ligne` : placer un breakpoint à la ligne line si macro instruction, à la première instruction correspondante
- `label label` : arrêt quand arrivée sur l'adresse pointée par le label
- `adress adresse` : arrêt quand arrivée sur l'adresse
- `adress debut offset` : 	arrêt quand arrivée dans l'intervalle [ adresse, adresse + offset [
- `instr instruction` : arrêt à chaque fois qu'on atteint une instruction de ce type (par exemple, add)
- `port numeroPort [out/in] [val]` : arrêt si lecture ou écriture sur le port spécifié , optionnellement avec une valeur particulière
- `clear num` où num est le numéro du point d'arrêt obtenu par la commande `info breakpoint` : efface le breakpoint

###Autres commandes en rapport

- `commands file` : charge un fichier avec des commandes pour le débugger, à exécuter quand un breakpoint est atteint ou une instruction "catchée"
- `symbols file` charge un fichiers de symbole (fichiers .log générés par l'assembleur)


## data

`display type arguments`

###Type
- `register [numero] ` : affiche la valeur du registre numéro (ou de tous les registres s'il n'y a pas d'arguments
- `address debut [offset]` : affiche les valeurs à l'adresse [debut, offset+debut[

###Autre commandes de données

- `dump adresse offset fichier` : idem qu'avant, mais enregistre en plus dans fichier
- `find seq` : recherche dans la mémoire une séquence d'octets, renvoie la première occurence
- `find-next` : recherche l'occurence suivante
- `print texte` : affiche le texte en argument
- `write adresse val` : écrire à l'adresse spécifiée la valeur val
- `write adresse offset val` : écrire dans la région [adresse, adresse + offset[ la
	valeur val
- `write register val` : écrire dans le registre register la valeur val
- `write port num [out/in] val` : envoie la valeur val sur le port spécifié ou la lis

## files

- `file fichier` (ou file codeObjet codeAssembleur si les symboles ne sont pas dans le
	 fichier objet) : charge le fichier pour le débuggage
- `path chemin` : ajout du chemin aux chemins connus par le debugger

## Various
- `compare adresse offset fichier` : compare le dump conservé dans fichier avec 
le contenu de la mémoire [adresse, adresse + offset]
- `record fichier` : sauvegarde l'état de la machine dans un fichier
- `restore fichier` : restaure l'état de la machine à partir du fichier
- `exit` : arrêt du débuggage


## running 
- `continue` : continue l'exécution
- `c` : continue l'exécution
- `ctrl + c` : met en pause l'exécution du programme 
- `next` : instruction suivante
- `n` : instruction suivante
- `step n` : avance de n lignes
- `run` : lance l'exécution du dernier programme chargé
- `until` : exécution jusqu'à ce que le programme avance dans les instructions
	(pratique pour sauter une boucle : on s'arrête au moment du saut, on met until, 
	et le programme s'arrêtera au sortir de la boucle)


## stack : inspection de la pile matérielle, et de la pile pointée par R31
- `show stack n` : affichage du contenu de la mémoire sur n octets à partir de l'adresse (faire une détection automatique de la pile d'appel ?)
de début de pile
- `show callstack` : afficher le contenu de la pile d'appel
- `ret` : retourne immédiatement de l'appel (simule un ret)


## status (peut-être changer les noms des watchpoints etc pour être consistant avec gdb ?)
- `info breakpoint` : infos sur les breakpoints
- `info files` : affiche les fichiers chargés
- `info time` : temps depuis le début de l'exécution du programme (sans compter les arrêts)

## support 
- `! commande` : exécute une commande shell
- `help` : affiche l'aide
- `h` : idem
- `help commande` ou `h commande` : affiche l'aide d'une commande
- `source fichier` : exécute les commandes de débuggage présentes dans le fichier


## timing

Ajout de timing : pour mesurer la durée d'exécution

- `time start` : lancer le chronomètre
- `time stop` : arrêter le chronomètre
