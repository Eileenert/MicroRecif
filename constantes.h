/* constantes.h
Orjowane Kaki
Eileen Rheinboldt-Tran
*/
#include "shape.h" // nécessaire pour utiliser epsil_zero et disposer des symboles de graphic.h
enum Statut_cor {DEAD, ALIVE} ;
enum Dir_rot_cor {TRIGO, INVTRIGO} ;
enum Statut_sca {LIBRE, MANGE} ;
constexpr double maximum(256.) ; //j'ai changé max en maximum sinon il y avait une erreur
constexpr unsigned r_alg(1) ;
constexpr unsigned d_cor(3) ;
constexpr unsigned r_sca(3) ;
constexpr unsigned r_sca_repro(10) ;
constexpr unsigned delta_r_sca(1) ;
constexpr unsigned delta_l (4) ;
constexpr unsigned l_repro (40) ;
constexpr unsigned l_seg_interne (28) ;
constexpr double delta_rot(0.0625) ;
// en rd = env. 3.5°
constexpr double alg_birth_rate(0.5) ;
constexpr unsigned max_life_alg(500) ;
constexpr unsigned max_life_cor(1500) ;
constexpr unsigned max_life_sca(2000) ;