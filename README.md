# MicroRecif
MicroRecif project EPFL

syntaxe:
- indrémentation if et return
- classes


(Les fonctions qui sont encore à finaliser:) PAS POUR RENDU 1

- "bool Segments::superposition" (shape.cc) : 3.2.3 "s'il appartient à l'intervalle et change de signe lors de la mise à jour", j'ai pas        fait le truc du changement de signe 

Dans le module simulation : donc bool simulation = 1
    1) on doit demander 2 fois l'ecart angulaire à shape (avant la mise à jour, après la mise à jour), cela nous permet de verifier le signe 
    2) on verifie que l'ecart appartien à l'intervalle (-delta_rot, delta_rot)



