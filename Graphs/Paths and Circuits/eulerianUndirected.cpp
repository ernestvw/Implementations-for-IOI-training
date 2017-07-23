// C++ program to check if a eulerian circuit exists and if yes print it in an undirected graph
#include <cstdio>
#include <vector>
using namespace std;

const int MAX_NB_NOEUDS = 1000;
const int MAX_NB_ARCS = 10 * 1000;

struct Arete
{
   int autreNoeud;
   int id;
   Arete(int autreNoeud, int id) : autreNoeud(autreNoeud), id(id) {}
};

int dejaVu[MAX_NB_ARCS];
vector<Arete> aretesAdjacentes[MAX_NB_NOEUDS];

void AfficheCircuit(int noeud)
{
   for (int iArete = 0; iArete < aretesAdjacentes[noeud].size(); iArete++)
   {
      Arete arete = aretesAdjacentes[noeud][iArete];
      if (dejaVu[arete.id])
         continue;
      dejaVu[arete.id] = true;
      AfficheCircuit(arete.autreNoeud);
   }
   printf("%d ", noeud + 1);
}

int main()
{
   int nbNoeuds, nbAretes;
   scanf("%d%d", &nbNoeuds, &nbAretes);
   for (int arete = 0; arete < nbAretes; arete++)
   {
      int noeud1, noeud2;
      scanf("%d%d", &noeud1, &noeud2);
      noeud1--;
      noeud2--;
      aretesAdjacentes[noeud1].push_back(Arete(noeud2, arete));
      aretesAdjacentes[noeud2].push_back(Arete(noeud1, arete));
   }
   for (int noeud = 0; noeud < nbNoeuds; noeud++)
      if (aretesAdjacentes[noeud].size() % 2 != 0)
      {
         printf("-1\n");
         return 0;
      }
   AfficheCircuit(0);
   return 0;
}
