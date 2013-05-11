ASMSuite
========

Un ensemble d'outils pour un langage d'assemblage : assembleur, simulateur, débugger.


Structure
---------

L'assembleur est indépendant du simulateur et du debugger, qui sont eux plus 
ou moins liés.

Utilisation
-----------

* `assembler fichier.asm fichier.out`
* `debugger fichier.out [fichier.log]`

Plus d'informations dans les README des programmes.

Compilation
-----------

### Compilation globale

`make`

### Compilation d'un programme particulier

* `cd debugger #ou assembler ou simulator`
* `make`

### Dépendances et prérequis

g++ avec support de C++11
