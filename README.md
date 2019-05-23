# README (ANALYSE) :
Auteur : Lug Lemaitre

## How it's works

Pour utiliser l'analyseur il faut:
 1. Importer le fichier analysis/analisys.hpp
 2. Lancer l'analyse avec la fonction analyse (regarder la doc pour les paramètres)
 3. Si l'analyse ne retourne pas false ou si le programme ne s'arrête pas avec un message d'erreur l'allocation est réussite
 4. Envoyer la liste des processeurs de l'architecture au générateur (chaque processeur contient son taskset à jour)

## Fonction implantée[^1]

| Fonction                | Fait     | Testé    |
|-------------------------|----------|----------|
| alloc                   | &#x2611; | &#x2611; |
| generate_concretes_task | &#x2611; | &#x2611; |
| sort_concrete           | &#9746; | &#9746; |
| generate_path           | &#x2611; | &#x2611; |
| assign_deadline         | &#x2611; | &#x2611; |
| generate_tagged         | &#x2611; | &#x2611; |
| feasible_sequential     | &#x2611; | partiellement |
| select_engines          | &#x2611; | &#x2611; |
| sort_engines            | &#x2611; | &#x2611; |
| parrallelize            | &#x2611; | &#9746; |
| omit_remove             | only random | &#9746; |
| dbf_test (EDF prempt)   | &#x2611; | &#9746; |
| sort_concretes (both order) | &#x2611; | &#9746; |

[^1]: Celles dont je me souviens, si oubli m'envoyer un mail

## Générer la doc
```bash
$ make docs && firefox doc/html/index.html
```