# MicroRecif
MicroRecif project EPFL

syntaxe:

- classes


Les choses à vérifier :

- epsil_zero 
- incohérence : partie 4.2 du projet et 3.2.4 du rendu1 


Les fonctions qui sont encore à finaliser:

- "bool Segments::superposition" (shape.cc) : 3.2.3 "s'il appartient à l'intervalle et change de signe lors de la mise à jour", j'ai pas        fait le truc du changement de signe 

Dans le module simulation : donc bool simulation = 1
    1) on doit demander 2 fois l'ecart angulaire à shape (avant la mise à jour, après la mise à jour), cela nous permet de verifier le signe 
    2) on verifie que l'ecart appartien à l'intervalle (-delta_rot, delta_rot)

- "bool Lifeform::appartenance_recipient(bool simulation)" (Lifeform) : à finir 3.2.2, c'est quoi un effecteur ?
(- "double orientation" (shape.cc) : j'ai gardé la ligne, ça me parait plus logique)

voir :
shape.cc ligne 12


