#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data_structure.h"

#define NUM_DATA_PNTS 15
#define NUM_EXPS 10
#define SEARCH_OPS_COUNT 100000
#define MAX_TIME 600


double get_time() {
    return (double)clock()/CLOCKS_PER_SEC;
}

void generate_data(int** ids, int**scores, int n) {
    *ids = (int*)malloc(n * sizeof(int));
    *scores = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        (*ids)[i] = (rand() % MAX_ID) + 1; // id; random n 個 id 給我呼叫這個 function 的指標所指向的空間
        (*scores)[i] = rand() % 101;    // score
    }
}

/* Test for Insert */
double test_da_insert(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    DynamicArray* arr = newDynamicArray();
    double start = get_time();

    for(int i=0; i<n; i++) {
        DynamicArrayInsert(arr, ids[i], scores[i]);
    }

    double end = get_time();

    DynamicArrayFree(arr);
    free(ids);
    free(scores);

    return end - start;
}

double test_sa_insert(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    StaticArray* arr = newStaticArray();

    double start = get_time();

    for(int i=0; i<n; i++) {
        StaticArrayInsert(arr, ids[i], scores[i]);
    }

    double end = get_time();

    StaticArrayFree(arr);
    free(ids);
    free(scores);

    return end - start;
}

double test_llp_insert(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    LinkedListPro* list = newLinkedListPro();
    double start = get_time();

    for(int i=0; i<n; i++) {
        LinkedListProInsert(list, ids[i], scores[i]);
    }

    double end = get_time();

    LinkedListProFree(list);
    free(ids);
    free(scores);

    return end - start;
}

/* Test for Search */
double test_da_search(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    DynamicArray* arr = newDynamicArray();

    for(int i=0; i<n; i++) {
        DynamicArrayInsert(arr, ids[i], scores[i]);
    }
    // Generate search ids
    int* search_ids = (int*)malloc(SEARCH_OPS_COUNT * sizeof(int));
    for (int i = 0; i < SEARCH_OPS_COUNT; i++) {
        search_ids[i] = (rand() % MAX_ID) + 1; // Random id for searching
    }

    double start = get_time();

    for(int i=0; i<SEARCH_OPS_COUNT; i++) {
        int count = 0;
        int* result = DynamicArraySearch(arr, search_ids[i], &count);
        if (result) free(result);
    }

    double end = get_time();

    DynamicArrayFree(arr);
    free(ids);
    free(scores);
    free(search_ids);

    return end - start;
} 

double test_sa_search(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    StaticArray* arr = newStaticArray();

    for(int i=0; i<n; i++) {
        StaticArrayInsert(arr, ids[i], scores[i]);
    }
    // Generate search ids
    int* search_ids = (int*)malloc(SEARCH_OPS_COUNT * sizeof(int));
    for (int i = 0; i < SEARCH_OPS_COUNT; i++) {
        search_ids[i] = (rand() % MAX_ID) + 1; // Random id for searching
    }

    double start = get_time();

    for(int i=0; i<SEARCH_OPS_COUNT; i++) {
        int count = 0;
        int* result = StaticArraySearch(arr, search_ids[i], &count);
        if (result) free(result);
    }

    double end = get_time();

    StaticArrayFree(arr);
    free(ids);
    free(scores);
    free(search_ids);

    return end - start;
}

double test_llp_search(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);

    LinkedListPro* list = newLinkedListPro();
    for(int i=0; i<n; i++) {
        LinkedListProInsert(list, ids[i], scores[i]);
    }

    // Generate search ids
    int* search_ids = (int*)malloc(SEARCH_OPS_COUNT * sizeof(int));
    for (int i = 0; i < SEARCH_OPS_COUNT; i++) {
        search_ids[i] = (rand() % MAX_ID) + 1; // Random id for searching
    }

    double start = get_time();

    for(int i=0; i<SEARCH_OPS_COUNT; i++) {
        int count = 0;
        int* result = LinkedListProSearch(list, search_ids[i], &count);
        if (result) free(result);
    }

    double end = get_time();

    LinkedListProFree(list);
    free(ids);
    free(scores);
    free(search_ids);

    return end - start;

}

/* Test for Sum */
double test_da_sum(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    DynamicArray* arr = newDynamicArray();

    for(int i=0; i<n; i++) {
        DynamicArrayInsert(arr, ids[i], scores[i]);
    }

    double start = get_time();
    long long sum = DynamicArraySum(arr);
    double end = get_time();

    DynamicArrayFree(arr);
    free(ids);
    free(scores);

    return end - start;
}

double test_sa_sum(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    StaticArray* arr = newStaticArray();

    for(int i=0; i<n; i++) {
        StaticArrayInsert(arr, ids[i], scores[i]);
    }

    double start = get_time();
    long long sum = StaticArraySum(arr);
    double end = get_time();

    StaticArrayFree(arr);
    free(ids);
    free(scores);

    return end - start;
}

double test_llp_sum(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    LinkedListPro* list = newLinkedListPro();

    for(int i=0; i<n; i++) {
        LinkedListProInsert(list, ids[i], scores[i]);
    }

    double start = get_time();
    long long sum = LinkedListProSum(list);
    double end = get_time();

    LinkedListProFree(list);
    free(ids);
    free(scores);

    return end - start;
}

/* Estimate Function: if time exceed the limit, we estimate time with this function */
double estimate_time(double* time, int count, int target) {

    if(count < 2) {
        return -1.0; // Not enough data to estimate
    }
    int n1 = (count-1)*1000;
    int n2 = count*1000;
    double t1 = time[count-2];
    double t2 = time[count-1];

    double slope = (t2 - t1) / (n2 - n1);
    double estimated_time = t2 + slope * (target - n2);

    return estimated_time > 0 ? estimated_time : -1.0;

}

/* Test for Memory Usage */
size_t test_da_memory(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    DynamicArray* arr = newDynamicArray();

    for(int i=0; i<n; i++) {
        DynamicArrayInsert(arr, ids[i], scores[i]);
    }

    size_t memory = DynamicArrayMemoryUsage(arr);

    DynamicArrayFree(arr);
    free(ids);
    free(scores);

    return memory;
}

size_t test_sa_memory(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    StaticArray* arr = newStaticArray();

    for(int i=0; i<n; i++) {
        StaticArrayInsert(arr, ids[i], scores[i]);
    }

    size_t memory = StaticArrayMemoryUsage(arr);

    StaticArrayFree(arr);
    free(ids);
    free(scores);

    return memory;
}

size_t test_llp_memory(int n) {
    int* ids;
    int* scores;
    generate_data(&ids, &scores, n);
    LinkedListPro* list = newLinkedListPro();

    for(int i=0; i<n; i++) {
        LinkedListProInsert(list, ids[i], scores[i]);
    }

    size_t memory = LinkedListProMemoryUsage(list);

    LinkedListProFree(list);
    free(ids);
    free(scores);

    return memory;
}

/* Experiments */
void exp_1() {
    /*
        記錄執行 n 次 insert 所需要的時間，我需要的資料是產生 15 個資料點，每個資料點為 10 筆實驗值取平均
        總共執行 150 次實驗
    */
    FILE* output_file = fopen("exp1_results.csv", "w+");
    if (!output_file) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }
    fprintf(output_file, "DynamicArray,StaticArray,LinkedListPro\n");

    // Store the history for time estimation
    double da_history[NUM_DATA_PNTS];
    double sa_history[NUM_DATA_PNTS];
    double llp_history[NUM_DATA_PNTS];
    int n_history[NUM_DATA_PNTS];
    int history_count = 0;

    for (int pnt=0; pnt<NUM_DATA_PNTS; pnt++) {

        int n = (pnt+1)*1000; // insert different data amount to see the performance
        double da_time = 0.0, sa_time = 0.0, llp_time = 0.0;
        int da_count = 0, sa_count = 0, llp_count = 0;
        printf("n %d times insert\n", n);
        fprintf(output_file, "n %d times insert\n", n);

        double da_start = get_time();
        int da_timeout = 0;
        
        // Dynamic Array
        printf("Dynamic Array\n");
        fprintf(output_file, "Dynamic Array\n");
        for(int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - da_start > MAX_TIME) {
                da_timeout = 1;
                break;
            }

            double t = test_da_insert(n);
            da_time += t;
            da_count++;
            }

        if(da_timeout) {
            // Estimate time
            double est = estimate_time(da_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            } else {
                printf("%d point time: Time out!\n", pnt+1);
                fprintf(output_file, "%d point time: Time out!\n", pnt+1);
            }
            
        } else {
            double avg = da_time / da_count;
            da_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        double sa_start = get_time();
        int sa_timeout = 0;

        // Static Array
        printf("Static Array\n");
        fprintf(output_file, "Static Array\n");
        for(int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - sa_start > MAX_TIME) {
                sa_timeout = 1;
                break;
            }

            double t = test_sa_insert(n);
            sa_time += t;
            sa_count++;
        }

        if(sa_timeout) {
            // Estimate time
            double est = estimate_time(sa_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            } else {
                printf("%d point time: Time out!\n", pnt+1);
                fprintf(output_file, "%d point time: Time out!\n", pnt+1);
            }
        } else {
            double avg = sa_time / sa_count;
            sa_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        double llp_start = get_time();
        int llp_timeout = 0;

        // Linked List Pro
        printf("Linked List Pro\n");
        fprintf(output_file, "Linked List Pro\n");
        for(int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - llp_start > MAX_TIME) {
                llp_timeout = 1;
                break;
            }
            double t = test_llp_insert(n);
            llp_time += t;
            llp_count++;
        }
        if(llp_timeout) {
            // Estimate time
            double est = estimate_time(llp_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            }
        } else {
            double avg = llp_time / llp_count;
            llp_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }
        
        printf("\n");
        history_count++;

    }
    printf("\n");
    fclose(output_file);
}

void exp_2() {
    /*
        記錄執行 100,000 次 search 所需要的時間，我需要的資料是產生 15 個資料點，每個資料點為 10 筆實驗值取平均
        總共執行 150 次實驗
    */
    FILE* output_file = fopen("exp2_results.csv", "w+");
    if (!output_file) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }
    fprintf(output_file, "DynamicArray,StaticArray,LinkedListPro\n");

    // Store the history for time estimation
    double da_history[NUM_DATA_PNTS];
    double sa_history[NUM_DATA_PNTS];
    double llp_history[NUM_DATA_PNTS];
    int n_history[NUM_DATA_PNTS];
    int history_count = 0;

    for (int pnt=0; pnt<NUM_DATA_PNTS; pnt++) {
        int n = (pnt+1)*1000;

        double da_time = 0.0, sa_time = 0.0, llp_time = 0.0;
        int da_count = 0, sa_count = 0, llp_count = 0;
        printf("n %d times insert\n", n);

        double da_start = get_time();
        int da_timeout = 0;

        // Dynamic Array
        printf("Dynamic Array\n");
        fprintf(output_file, "Dynamic Array\n");
        for (int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - da_start > MAX_TIME) {
                da_timeout = 1;
                break;
            }

            double t = test_da_search(n);
            da_time += t;
            da_count++;
        }
        if (da_timeout) {
            // Estimate time
            double est = estimate_time(da_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            } else {
                printf("%d point time: Time out!\n", pnt+1);
                fprintf(output_file, "%d point time: Time out!\n", pnt+1);
            }
        } else {
            double avg = da_time / da_count;
            da_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        double sa_start = get_time();
        int sa_timeout = 0;

        // Static Array
        printf("Static Array\n");
        fprintf(output_file, "Static Array\n");
        for (int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - sa_start > MAX_TIME) {
                sa_timeout = 1;
                break;
            }

            double t = test_sa_search(n);
            sa_time += t;
            sa_count++;
        }
        if (sa_timeout) {
            // Estimate time
            double est = estimate_time(sa_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            } else {
                printf("%d point time: Time out!\n", pnt+1);
                fprintf(output_file, "%d point time: Time out!\n", pnt+1);
            }
        } else {
            double avg = sa_time / sa_count;
            sa_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        double llp_start = get_time();
        int llp_timeout = 0;

        // Linked List Pro
        printf("Linked List Pro\n");
        fprintf(output_file, "Linked List Pro\n");
        for (int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - llp_start > MAX_TIME) {
                llp_timeout = 1;
                break;
            }
            double t = test_llp_search(n);
            llp_time += t;
            llp_count++;
        }
        if (llp_timeout) {
            // Estimate time
            double est = estimate_time(llp_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            }
        } else {
            double avg = llp_time / llp_count;
            llp_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        printf("\n");
        history_count++;
    }

    printf("\n");
    fclose(output_file);
}

void exp_3() {
    /*
        記錄執行 n 次 sum 所需要的時間，我需要的資料是產生 15 個資料點，每個資料點為 10 筆實驗值取平均
        總共執行 150 次實驗
    */
    FILE* output_file = fopen("exp3_results.csv", "w+");
    if (!output_file) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }
    fprintf(output_file, "DynamicArray,StaticArray,LinkedListPro\n");
    
    // Store the history for time estimation
    double da_history[NUM_DATA_PNTS];
    double sa_history[NUM_DATA_PNTS];
    double llp_history[NUM_DATA_PNTS];
    int n_history[NUM_DATA_PNTS];
    int history_count = 0;

    for (int pnt=0; pnt<NUM_DATA_PNTS; pnt++) {
        int n = (pnt+1)*1000;

        double da_time = 0.0, sa_time = 0.0, llp_time = 0.0;
        int da_count = 0, sa_count = 0, llp_count = 0;
        printf("n %d times insert\n", n);

        double da_start = get_time();
        int da_timeout = 0;

        // Dynamic Array
        printf("Dynamic Array\n");
        fprintf(output_file, "Dynamic Array\n");
        for (int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - da_start > MAX_TIME) {
                da_timeout = 1;
                break;
            }

            double t = test_da_sum(n);
            da_time += t;
            da_count++;
        }
        if (da_timeout) {
            // Estimate time
            double est = estimate_time(da_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            } else {
                printf("%d point time: Time out!\n", pnt+1);
                fprintf(output_file, "%d point time: Time out!\n", pnt+1);
            }
        } else {
            double avg = da_time / da_count;
            da_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        double sa_start = get_time();
        int sa_timeout = 0;

        // Static Array
        printf("Static Array\n");
        fprintf(output_file, "Static Array\n");
        for (int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - sa_start > MAX_TIME) {
                sa_timeout = 1;
                break;
            }

            double t = test_sa_sum(n);
            sa_time += t;
            sa_count++;

        }
        if (sa_timeout) {
            // Estimate time
            double est = estimate_time(sa_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            } else {
                printf("%d point time: Time out!\n", pnt+1);
                fprintf(output_file, "%d point time: Time out!\n", pnt+1);
            }
        } else {
            double avg = sa_time / sa_count;
            sa_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        double llp_start = get_time();
        int llp_timeout = 0;

        // Linked List Pro
        printf("Linked List Pro\n");
        fprintf(output_file, "Linked List Pro\n");
        for (int exp=0; exp<NUM_EXPS; exp++) {
            if (get_time() - llp_start > MAX_TIME) {
                llp_timeout = 1;
                break;
            }
            double t = test_llp_sum(n);
            llp_time += t;
            llp_count++;
        }
        if (llp_timeout) {
            // Estimate time
            double est = estimate_time(llp_history, history_count, n);
            if(est>0) {
                printf("%d point time: %.6f (estimated)\n", pnt+1, est);
                fprintf(output_file, "%d point time: %.6f (estimated)\n", pnt+1, est);
            }
        } else {
            double avg = llp_time / llp_count;
            llp_history[history_count] = avg;
            printf("%d point time: %.6f\n", pnt+1, avg);
            fprintf(output_file, "%d point time: %.6f\n", pnt+1, avg);
        }

        printf("\n");
        history_count++;
    }

    printf("\n");
    fclose(output_file);
}

void exp_4() {
    /*
        測試插入 n 筆資料後三種資料結構的記憶體使用量
    */
    FILE* output_file = fopen("exp4_results.csv", "w+");
    if (!output_file) {
        fprintf(stderr, "Error opening file for writing.\n");
        return;
    }
    fprintf(output_file, "DynamicArray,StaticArray,LinkedListPro\n");

    for (int pnt=0; pnt<NUM_DATA_PNTS; pnt++) {
        int n = (pnt+1)*1000;

        printf("n %d times insert\n", n);
        fprintf(output_file, "n %d times insert\n", n);

        // Dynamic Array
        size_t da_memory = test_da_memory(n);
        printf("Dynamic Array memory: %zu bytes (%.2f KB)\n", da_memory, da_memory/1024.0);
        fprintf(output_file, "Dynamic Array memory: %zu bytes (%.2f KB)\n", da_memory, da_memory/1024.0);

        // Static Array
        size_t sa_memory = test_sa_memory(n);
        printf("Static Array memory: %zu bytes (%.2f KB)\n", sa_memory, sa_memory/1024.0);
        fprintf(output_file, "Static Array memory: %zu bytes(%.2f KB)\n", sa_memory, sa_memory/1024.0);

        // Linked List Pro
        size_t llp_memory = test_llp_memory(n);
        printf("Linked List Pro memory: %zu bytes (%.2f KB)\n", llp_memory, llp_memory/1024.0);
        fprintf(output_file, "Linked List Pro memory: %zu bytes (%.2f KB)\n", llp_memory, llp_memory/1024.0);

        printf("\n");
    }
}
int main() {
    srand(time(NULL));

    int choice;
    printf("Choose experiment to run (1: Insert, 2: Search, 3: Sum, 4: Memory): ");
    scanf("%d", &choice);

    if (choice == 1) {
        exp_1();
    } else if (choice == 2) {
        exp_2();
    } else if (choice == 3) {
        exp_3();
    } else if (choice == 4) {
        exp_4();
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}





