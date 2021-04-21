#ifdef DATA_TYPE
#ifdef TYPE_NAME
#ifdef IO_FORMAT

#define TRUE 1
#define FALSE 0
#define EPSILON 0.0001

struct TYPE_NAME(vect_s)
{
	int amountElements;
	int maxCapacity;
	int index;
	DATA_TYPE *array;
};

void TYPE_NAME(adjustVector)(TYPE_NAME(vect_t *) vector)
{
	if (vector->amountElements >= vector->maxCapacity)
	{
		vector->maxCapacity *= 2;
	}
	if (vector->amountElements < (vector->maxCapacity)/4)
	{
		vector->maxCapacity /= 2;
	}

	vector->array = (DATA_TYPE *) realloc(vector->array, vector->maxCapacity * sizeof(DATA_TYPE));
}

TYPE_NAME(vect_t *) TYPE_NAME(createVector)(int n, int i)
{
	TYPE_NAME(vect_t) *vector = (TYPE_NAME(vect_t *)) malloc(sizeof(TYPE_NAME(vect_t)));
	vector->amountElements = n;
	vector->maxCapacity = 100;
	vector->index = i;
	vector->array = (DATA_TYPE *) malloc(vector->maxCapacity * sizeof(DATA_TYPE));

	for (int j = 0; j < vector->maxCapacity; j++)
	{
		*(vector->array + j) = 0;
	}

	TYPE_NAME(adjustVector)(vector);

	return vector;
}

void TYPE_NAME(freeVector)(TYPE_NAME(vect_t *) vector)
{
	if (vector != NULL)
	{
		if (vector->array != NULL)
		{
			free(vector->array);
			vector->array = NULL;
		}

		free(vector);
		vector = NULL;
	}
}

void TYPE_NAME(copyToExistingVector)(TYPE_NAME(vect_t *) v1, TYPE_NAME(vect_t *) v2)
{
	v2->amountElements = v1->amountElements;
	v2->maxCapacity = v1->maxCapacity;
	v2->index = v1->index;
	v2->array = (DATA_TYPE *) realloc(v2->array, v2->maxCapacity * sizeof(DATA_TYPE));

	for (int i = 0; i < v1->maxCapacity; i++)
	{
		*(v2->array + i) = *(v1->array + i);
	}

	TYPE_NAME(adjustVector)(v1);
	TYPE_NAME(adjustVector)(v2);
}

TYPE_NAME(vect_t *) TYPE_NAME(copyToNewVector)(TYPE_NAME(vect_t *) v1)
{
	TYPE_NAME(vect_t) *v2 = TYPE_NAME(createVector)(50, 0);

	v2->amountElements = v1->amountElements;
	v2->maxCapacity = v1->maxCapacity;
	v2->index = v1->index;
	v2->array = (DATA_TYPE *) realloc(v2->array, v2->maxCapacity * sizeof(DATA_TYPE));

	for (int i = 0; i < v1->maxCapacity; i++)
	{
		*(v2->array + i) = *(v1->array + i);
	}

	TYPE_NAME(adjustVector)(v1);
	TYPE_NAME(adjustVector)(v2);

	return v2;
}

int TYPE_NAME(getAmountElements)(TYPE_NAME(vect_t *) vector)
{
	return vector->amountElements;
}

int TYPE_NAME(getMaxCapacity)(TYPE_NAME(vect_t *) vector)
{
	return vector->maxCapacity;
}

int TYPE_NAME(getIndex)(TYPE_NAME(vect_t *) vector)
{
	return vector->index;
}

DATA_TYPE TYPE_NAME(getFirstElement)(TYPE_NAME(vect_t *) vector)
{
	vector->index = 0;

	return *(vector->array + vector->index);
}

DATA_TYPE TYPE_NAME(getNextElement)(TYPE_NAME(vect_t *) vector)
{
	vector->index += 1;

	return *(vector->array + vector->index);
}

DATA_TYPE TYPE_NAME(getPrevElement)(TYPE_NAME(vect_t *) vector)
{
	vector->index -= 1;

	return *(vector->array + vector->index);
}

DATA_TYPE TYPE_NAME(getLastElement)(TYPE_NAME(vect_t *) vector)
{
	vector->index = vector->amountElements;

	return *(vector->array + vector->index);
}

DATA_TYPE TYPE_NAME(getElementByIndex)(TYPE_NAME(vect_t *) vector, int i)
{
	if (i > vector->amountElements)
	{
		vector->index = vector->amountElements - 1;
	}
	else
	{
		vector->index = i;
	}

	return *(vector->array + vector->index);
}

void TYPE_NAME(insertIndexPosValue)(TYPE_NAME(vect_t *) vector, DATA_TYPE v, int i)
{
	if (i >= 0 && i <= vector->amountElements)
	{
		vector->index = i;
		*(vector->array + vector->index) = v;
	}

	TYPE_NAME(adjustVector)(vector);
}

void TYPE_NAME(insertLastPosValue)(TYPE_NAME(vect_t *) vector, DATA_TYPE v)
{
	vector->amountElements++;
	vector->index = vector->amountElements - 1;

	*(vector->array + vector->index) = v;

	TYPE_NAME(adjustVector)(vector);
}

DATA_TYPE TYPE_NAME(deletePosition)(TYPE_NAME(vect_t *) vector, int i)
{
	for (int j = i; j < vector->amountElements; j++)
	{
		*(vector->array + j) = *(vector->array + (j+1));
	}
	vector->amountElements--;

	TYPE_NAME(adjustVector)(vector);

	return *(vector->array + i);
}

void TYPE_NAME(clearAllVector)(TYPE_NAME(vect_t *) vector)
{
	for (int i = 0; i <= vector->amountElements; i++)
	{
		*(vector->array + i) = 0;
	}
	vector->amountElements = 2;

	TYPE_NAME(adjustVector)(vector);
}

DATA_TYPE TYPE_NAME(getBiggestAbs)(TYPE_NAME(vect_t *) vector)
{
	DATA_TYPE higherValue = 0;

	for (int i = 0; i < vector->amountElements; i++)
	{
		if (abs(*(vector->array + i)) > higherValue)
		{
			higherValue = *(vector->array + i);
			vector->index = i;
		}
	}

	return higherValue;
}

DATA_TYPE TYPE_NAME(getSmallestAbs)(TYPE_NAME(vect_t *) vector)
{
	DATA_TYPE lowerValue = 0;

	for (int i = 0; i < vector->amountElements; i++)
	{
		if (abs(*(vector->array + i)) < lowerValue)
		{
			lowerValue = *(vector->array + i);
			vector->index = i;
		}
	}

	return lowerValue;
}

int TYPE_NAME(countEquals)(TYPE_NAME(vect_t *) vector, DATA_TYPE value)
{
	int count = 0;
	DATA_TYPE vecValue = 0;

	for (int i = 0; i < vector->amountElements; i++)
	{
		vecValue = *(vector->array + i);

		if (TYPE_NAME(diffValues)(vecValue, value) <= EPSILON)
		{
			count++;
		}
	}

	return count;
}

TYPE_NAME(vect_t *) TYPE_NAME(indexOfEquals)(TYPE_NAME(vect_t *) vector, DATA_TYPE value)
{
	int count = 0;
	DATA_TYPE vecValue = 0;
	TYPE_NAME(vect_t) *indexVector = TYPE_NAME(createVector)(1, 0);
	indexVector->index = 0;

	for (int i = 0; i < vector->amountElements; i++)
	{
		vecValue = *(vector->array + i);

		if (TYPE_NAME(diffValues)(vecValue, value) <= EPSILON)
		{
			*(indexVector->array + count) = (DATA_TYPE) i;
			count++;
			indexVector->amountElements = count;
			TYPE_NAME(adjustVector)(indexVector);
		}
	}
	indexVector->amountElements = count;
	TYPE_NAME(adjustVector)(indexVector);

	return indexVector;
}

void TYPE_NAME(sortVector)(TYPE_NAME(vect_t *) vector, TYPE_NAME(fptrI_DD) criteria) /* without typedef it would be necessary to insert all function pointer notation */
{
	int shift = TRUE, i, j;
	DATA_TYPE memory;
	int size = TYPE_NAME(getAmountElements)(vector);

	for (j = (size - 1); (j >= 1) && (shift); j--)
	{
		shift = FALSE;

		for (i = 0; i < j; i++)
		{
			DATA_TYPE value1 = TYPE_NAME(getElementByIndex)(vector, i);
			DATA_TYPE value2 = TYPE_NAME(getElementByIndex)(vector, i+1);

			if (criteria(value1, value2) == 1)
			{
				memory = *(vector->array + i);
				*(vector->array + i) = *(vector->array + (i+1));
				*(vector->array + (i+1)) = memory;
				shift = TRUE;
			}
		}
	}
}

TYPE_NAME(vect_t *) TYPE_NAME(regularlyInsert)(TYPE_NAME(vect_t *) vector1, TYPE_NAME(vect_t *) vector2, TYPE_NAME(fptrI_DD) criteria)
{
	int size1 = TYPE_NAME(getAmountElements)(vector1), size2 = TYPE_NAME(getAmountElements)(vector2);
	TYPE_NAME(sortVector)(vector1, TYPE_NAME(sortingCriter));
	TYPE_NAME(sortVector)(vector2, &TYPE_NAME(sortingCriter)); // reference operator '&' unnecessary
	int j = 0;

	if (size1 != size2)
	{
		printf("Your vectors don't have the same amount of elements!");
		exit(1);
	}

	TYPE_NAME(vect_t) *newVec = TYPE_NAME(createVector)(size1+size2, 0);

	for (int i = 0; (i < TYPE_NAME(getAmountElements)(newVec)) && (j < size1) && (j < size2); i += 2) /*  for (int i = 0; (i < TYPE_NAME(getAmountElements)(newVec)) && (criteria(j, size1) == -1) && (criteria(j, size2) == -1); i += 2)  */
	{
		*(newVec->array + i) = TYPE_NAME(getElementByIndex)(vector1, j);
		*(newVec->array + (i+1)) = TYPE_NAME(getElementByIndex)(vector2, j);
		j++;
	}
	TYPE_NAME(adjustVector)(newVec);

	return newVec;
}


TYPE_NAME(vect_t *) TYPE_NAME(sumVectors)(TYPE_NAME(vect_t *) vector1, TYPE_NAME(vect_t *) vector2)
{
	DATA_TYPE sum = 0;
	int amountElementsVector1 = TYPE_NAME(getAmountElements)(vector1);
	int amountElementsVector2 = TYPE_NAME(getAmountElements)(vector2);

	if (amountElementsVector1 != amountElementsVector2)
	{
		printf("Your vectors don't have the same amount of elements!");
		exit(1);
	}

	TYPE_NAME(vect_t *) sumVector = TYPE_NAME(createVector)(amountElementsVector1, 0);

	for (int i = 0; i < amountElementsVector1; i++)
	{
		sum = TYPE_NAME(getElementByIndex)(vector1, i) + TYPE_NAME(getElementByIndex)(vector2, i);
		TYPE_NAME(insertIndexPosValue)(sumVector, sum, i);
	}

	TYPE_NAME(adjustVector)(sumVector);

	return sumVector;
}

TYPE_NAME(vect_t *) TYPE_NAME(subtractVectors)(TYPE_NAME(vect_t *) vector1, TYPE_NAME(vect_t *) vector2)
{
	DATA_TYPE sub = 0;
	int amountElementsVector1 = TYPE_NAME(getAmountElements)(vector1);
	int amountElementsVector2 = TYPE_NAME(getAmountElements)(vector2);

	if (amountElementsVector1 != amountElementsVector2)
	{
		printf("Your vectors don't have the same amount of elements!");
		exit(1);
	}

	TYPE_NAME(vect_t *) subVector = TYPE_NAME(createVector)(amountElementsVector1, 0);

	for (int i = 0; i < amountElementsVector1; i++)
	{
		sub = TYPE_NAME(getElementByIndex)(vector1, i) - TYPE_NAME(getElementByIndex)(vector2, i);
		TYPE_NAME(insertIndexPosValue)(subVector, sub, i);
	}

	TYPE_NAME(adjustVector)(subVector);

	return subVector;
}

void TYPE_NAME(multiplyVectorByScalar)(TYPE_NAME(vect_t *) vector, DATA_TYPE scalar)
{
	DATA_TYPE multi = 0;

	for (int i = 0; i < TYPE_NAME(getAmountElements)(vector); i++)
	{
		multi = scalar * TYPE_NAME(getElementByIndex)(vector, i);
		TYPE_NAME(insertIndexPosValue)(vector, multi, i);
	}
}

double TYPE_NAME(calculateScalarProduct)(TYPE_NAME(vect_t *) vector1, TYPE_NAME(vect_t *) vector2)
{
	double scalarProduct = 0;
	int amountElementsVector1 = TYPE_NAME(getAmountElements)(vector1);
	int amountElementsVector2 = TYPE_NAME(getAmountElements)(vector2);

	if (amountElementsVector1 != amountElementsVector2)
	{
		printf("Your vectors don't have the same amount of elements!");
		exit(1);
	}

	for (int i = 0; i < amountElementsVector1; i++)
	{
		scalarProduct += (TYPE_NAME(getElementByIndex)(vector1, i) * TYPE_NAME(getElementByIndex)(vector2, i));
	}

	return scalarProduct;
}

void TYPE_NAME(accumulateVectors)(TYPE_NAME(vect_t *) vector1, TYPE_NAME(vect_t *) vector2)
{
	DATA_TYPE acc = 0;
	int amountElementsVector1 = TYPE_NAME(getAmountElements)(vector1);
	int amountElementsVector2 = TYPE_NAME(getAmountElements)(vector2);

	if (amountElementsVector1 != amountElementsVector2)
	{
		printf("Your vectors don't have the same amount of elements!");
		exit(1);
	}

	for (int i = 0; i < amountElementsVector1; i++)
	{
		acc = TYPE_NAME(getElementByIndex)(vector1, i) + TYPE_NAME(getElementByIndex)(vector2, i);
		TYPE_NAME(insertIndexPosValue)(vector1, acc, i);
	}

	TYPE_NAME(adjustVector)(vector1);
}

double TYPE_NAME(calculateMean)(TYPE_NAME(vect_t *) vector)
{
	double mean = 0;

	for (int i = 0; i < (TYPE_NAME(getAmountElements)(vector)); i++)
	{
		mean += TYPE_NAME(getElementByIndex)(vector, i);
	}
	mean = mean / (TYPE_NAME(getAmountElements)(vector));

	return mean;
}

double TYPE_NAME(calculateVariance)(TYPE_NAME(vect_t *) vector)
{
	double mean = TYPE_NAME(calculateMean)(vector);
	double var = 0;

	for (int i = 0; i < (TYPE_NAME(getAmountElements)(vector)); i++)
	{
		var += pow((TYPE_NAME(getElementByIndex)(vector, i) - mean), 2);
	}
	var = var / ((TYPE_NAME(getAmountElements)(vector)) - 1);

	return var;
}

double TYPE_NAME(calculateDeviation)(TYPE_NAME(vect_t *) vector)
{
	return sqrt(TYPE_NAME(calculateVariance)(vector));
}

double TYPE_NAME(calculateMedianUsually)(TYPE_NAME(vect_t *) vector)
{
	double median = 0;
	int size = TYPE_NAME(getAmountElements)(vector);
	TYPE_NAME(vect_t) *newVector = TYPE_NAME(createVector)(vector->amountElements, vector->index);

	TYPE_NAME(accumulateVectors)(newVector, vector);
	TYPE_NAME(sortVector)(newVector, TYPE_NAME(sortingCriter));

	if (TYPE_NAME(getAmountElements)(newVector) % 2 == 0)
	{
		median = TYPE_NAME(getElementByIndex)(newVector, (size-1)/2) + TYPE_NAME(getElementByIndex)(newVector, (size-1)/2 + 1);
		median = median / 2.0;
	}
	else
	{
		median = TYPE_NAME(getElementByIndex)(newVector, (size-1)/2 + 1);
	}
	TYPE_NAME(freeVector)(newVector);

	return median;
}

/*
*	The following code is public domain.
*	Algorithm by Torben Mogensen, implementation by N. Devillard.
*	This code in public domain.
*/
double TYPE_NAME(calculateMedianTorben)(TYPE_NAME(vect_t *) vector)
{
	DATA_TYPE min = 0, max = 0, guess, maxltguess, mingtguess;
	int i, less, greater, equal;
	int size = TYPE_NAME(getAmountElements)(vector);

	min = max = TYPE_NAME(getElementByIndex)(vector, 0);

	for (i = 1; i < size; i++)
	{
		if (*(vector->array + i) < min)
			min = *(vector->array + i);
		if (*(vector->array + i) > max)
			max = *(vector->array + i);
	}

	while (1)
	{
		guess = (min+max)/2;
		less = 0; greater = 0; equal = 0;
		maxltguess = min;
		mingtguess = max;
		for (i = 0; i < size; i++)
		{
			if (*(vector->array + i) < guess)
			{
				less++;
				if (*(vector->array + i) > maxltguess)
					maxltguess = *(vector->array + i);
			}
			else if (*(vector->array + i) > guess)
			{
				greater++;
				if (*(vector->array + i) < mingtguess)
					mingtguess = *(vector->array + i);
			}
			else
				equal++;
		}
		if (less <= (size+1)/2 && greater <= (size+1)/2)
			break;
		else if (less > greater)
			max = maxltguess;
		else
			min = mingtguess;
	}
	if (less >= (size+1)/2)
		return (double) maxltguess;
	else if (less+equal >= (size+1)/2)
		return (double) guess;
	else
		return (double) mingtguess;
}

/*
*	This Quickselect routine is based on the algorithm described in
*	"Numerical recipes in C", Second Edition,
*	Cambridge University Press, 1992, Section 8.5, ISBN 0-521-43108-5
*	This code by Nicolas Devillard - 1998. Public domain.
*/
#define ELEM_SWAP(a, b) { register DATA_TYPE t=(a); (a)=(b); (b)=t; }
double TYPE_NAME(calculateMedianQuickSelect)(TYPE_NAME(vect_t *) vector)
{
	int low = 0, high = TYPE_NAME(getAmountElements)(vector)-1;
	int median = (low + high) / 2;
	int middle, ll, hh;

	for (0; TRUE; 0)
	{
		if (high <= low) /* One element only */
			return *(vector->array + median);

		if (high == low + 1)
		{  /* Two elements only */
			if (*(vector->array + low) > *(vector->array + high))
				ELEM_SWAP(*(vector->array + low), *(vector->array + high));
			return *(vector->array + median);
		}

		/* Find median of low, middle and high items; swap into position low */
		middle = (low + high) / 2;
		if (*(vector->array + middle) > *(vector->array + high))
			ELEM_SWAP(*(vector->array + middle), *(vector->array + high));
		if (*(vector->array + low) > *(vector->array + high))
			ELEM_SWAP(*(vector->array + low), *(vector->array + high));
		if (*(vector->array + middle) > *(vector->array + low))
			ELEM_SWAP(*(vector->array + middle), *(vector->array + low));

		/* Swap low item (now in position middle) into position (low+1) */
		ELEM_SWAP(*(vector->array + middle), *(vector->array + low+1));

		/* Nibble from each end towards middle, swapping items when stuck */
		ll = low + 1;
		hh = high;
		for (0; TRUE; 0)
		{
			do ll++; while (*(vector->array + low) > *(vector->array + ll));
			do hh--; while (*(vector->array + hh)  > *(vector->array + low));

			if (hh < ll)
			break;

			ELEM_SWAP(*(vector->array + ll), *(vector->array + hh));
		}

		/* Swap middle item (in position low) back into correct position */
		ELEM_SWAP(*(vector->array + low), *(vector->array + hh));

		/* Re-set active partition */
		if (hh <= median)
			low = ll;
		if (hh >= median)
			high = hh - 1;
	}
}
#undef ELEM_SWAP

int TYPE_NAME(sortingCriter)(DATA_TYPE a, DATA_TYPE b)
{
	if (a == b)
		return 0;
	if (a > b)
		return 1;
	if (a < b)
		return -1;
}

float TYPE_NAME(diffValues)(DATA_TYPE v1, DATA_TYPE v2)
{
	if (v1 >= v2)
		return (v1 - v2);
	else
		return (v2 - v1);
}

void TYPE_NAME(displayVector)(TYPE_NAME(vect_t *) vector)
{
	printf("\n\n");
	for (int i = 0; i < vector->amountElements; i++)
	{
		printf(IO_FORMAT, *(vector->array + i));
		printf(", ");
	}
	printf("\n\n");
}

#endif
#endif
#endif