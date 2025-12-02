# Pipex - 42

Pipex est un projet du cursus 42 qui a pour objectif de **répliquer le comportement d’une chaîne de commandes shell avec redirections et pipes**, en utilisant uniquement le langage C. Ce projet permet de comprendre la gestion des processus, des redirections et des pipes sous UNIX.

## Objectifs principaux

- **Comprendre la création et la gestion de processus** avec `fork()`.  
- **Apprendre à utiliser les pipes** (`pipe()`) pour la communication entre processus.  
- **Gérer les redirections d’entrée et de sortie** (`dup2()`).  
- **Répliquer le comportement des commandes shell** en combinant plusieurs processus et pipes.  
- **Développer une rigueur dans la manipulation des fichiers et des erreurs**.

## Fonctionnement

Le projet consiste à exécuter des commandes successives en simulant la syntaxe shell :

    ./pipex file1 cmd1 cmd2 file2

Ce qui est équivalent à la commande shell :  


    < file1 cmd1 | cmd2 > file2

- file1 : fichier d’entrée
- file2 : fichier de sortie
- cmd1, cmd2 : commandes à exécuter

Le programme doit gérer toutes les erreurs possibles : fichiers inexistants, commandes invalides, problèmes de pipe ou fork.
Compilation

Pour compiler le projet, utilisez :

    make

Exemple d'utilisation

    ./pipex input.txt "grep hello" "wc -l" output.txt

- Lit le fichier input.txt,
- Filtre les lignes contenant "hello" avec grep hello,
- Compte le nombre de lignes avec wc -l,
- Écrit le résultat dans output.txt.
