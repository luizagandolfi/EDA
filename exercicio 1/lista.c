#include <stdlib.h>
#include "lista.h"

void inicializa(lista *l, int (*cmp)(lista_item i1, lista_item i2))
{
	// implementar
	lista_no *sentinela = malloc(sizeof(lista_no));
	sentinela->ant = sentinela->prox = sentinela;
	l->sentinela = sentinela;
	l->quantidade = 0;
	l->compara = cmp;
}

void destroi(lista *l)
{
	while (!vazia(l))
		retira(l, elemento(primeiro(l)));
	free(l->sentinela);
}

int vazia(lista *l)
{
	return l->sentinela->prox == l->sentinela;
}

void insere(lista *l, lista_item item)
{
	lista_iterador it;
	if (!vazia(l))
	{
		l->sentinela->item = item;
		lista_iterador it2 = primeiro(l);
		while (l->compara(elemento(it2), item) == -1 && l->sentinela != it2.p)
		{
			it2.p = it2.p->prox;
		}
		it.p = it2.p->ant;
	}
	else
	{
		it = primeiro(l);
	}
	// implementar

	lista_no *node = malloc(sizeof(lista_no));
	//Resolvendo o node novo
	node->item = item;
	node->prox = it.p->prox;
	node->ant = it.p;
	//
	it.p->prox = node;
	node->prox->ant = node;

	l->quantidade++;
}

void retira(lista *l, lista_item item)
{
	// implementar

	if (vazia(l))
		return;

	lista_iterador it = primeiro(l);
	lista_no *p = it.p;

	while (p != l->sentinela)
	{
		if (l->compara(p->item, item) == 1)
			break;

		if (l->compara(p->item, item) == 0)
		{
			lista_no *aux = p;
			p->ant->prox = p->prox;
			p->prox->ant = p->ant;
			p = p->prox;
			free(aux);
			l->quantidade--;
		}
		else
			p = p->prox;
	}
}

lista_iterador primeiro(lista *l)
{
	lista_iterador it;
	it.l = l;
	it.p = l->sentinela->prox;
	return it;
}

lista_iterador ultimo(lista *l)
{
	lista_iterador it;
	it.l = l;
	it.p = l->sentinela->ant;
	return it;
}
lista_item elemento(lista_iterador i)
{
	// implementar

	if (i.p == i.l->sentinela)
		return 0;
	else
		return i.p->item;
}

int proximo(lista_iterador *i)
{
	if (!acabou(*i))
	{
		i->p = i->p->prox;
		return 1;
	}
	return 0;
}

int anterior(lista_iterador *i)
{
	if (!acabou(*i))
	{
		i->p = i->p->ant;
		return 1;
	}
	return 0;
}

int acabou(lista_iterador i)
{
	// implementar
	return (i.l->sentinela == i.p);
}
