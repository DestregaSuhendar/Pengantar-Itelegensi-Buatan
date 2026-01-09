#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>  // untuk fungsi fabs

// Fungsi aktivasi step (binary)
int step_activation(float x) {
    if (x >= 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    // Data training: input dan target untuk fungsi AND
    float input[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    int target[4] = {0, 0, 0, 1};

    // Inisialisasi bobot dan bias dengan nilai random kecil
    float w1, w2, bias;
    srand(time(NULL));
    w1 = ((float)rand() / RAND_MAX) * 2 - 1; // range [-1, 1]
    w2 = ((float)rand() / RAND_MAX) * 2 - 1;
    bias = ((float)rand() / RAND_MAX) * 2 - 1;

    float learning_rate = 0.1;
    int max_epoch = 100;
    int epoch, i;

    printf("=== Program Perceptron untuk Fungsi AND ===\n");
    printf("Bobot awal: w1 = %.3f, w2 = %.3f, bias = %.3f\n", w1, w2, bias);
    printf("Learning rate: %.2f\n", learning_rate);
    printf("Max epoch: %d\n\n", max_epoch);

    // Proses training
    for (epoch = 0; epoch < max_epoch; epoch++) {
        int total_error = 0;
        printf("Epoch %d:\n", epoch + 1);

        for (i = 0; i < 4; i++) {
            // Hitung net input
            float net_input = (input[i][0] * w1) + (input[i][1] * w2) + bias;

            // Hitung output menggunakan fungsi aktivasi step
            int output = step_activation(net_input);

            // Hitung error
            int error = target[i] - output;

            // Update bobot dan bias jika ada error (perceptron learning rule)
            if (error != 0) {
                w1 += learning_rate * error * input[i][0];
                w2 += learning_rate * error * input[i][1];
                bias += learning_rate * error;
                total_error += abs(error);
            }

            printf("  Input: [%.0f, %.0f] Target: %d Output: %d Error: %d\n",
                   input[i][0], input[i][1], target[i], output, error);
        }

        // Jika tidak ada error, training berhenti (konvergen)
        if (total_error == 0) {
            printf("\nTraining berhasil konvergen pada epoch %d!\n", epoch + 1);
            break;
        }

        printf("  Total error: %d\n\n", total_error);
    }

    // Tampilkan bobot dan bias akhir
    printf("\n=== Hasil Akhir ===\n");
    printf("Bobot akhir: w1 = %.3f, w2 = %.3f, bias = %.3f\n", w1, w2, bias);

    // Uji perceptron dengan data training
    printf("\n=== Pengujian ===\n");
    for (i = 0; i < 4; i++) {
        float net_input = (input[i][0] * w1) + (input[i][1] * w2) + bias;
        int output = step_activation(net_input);
        printf("Input: [%.0f, %.0f] -> Output: %d (Target: %d) %s\n",
               input[i][0], input[i][1], output, target[i],
               output == target[i] ? "(Benar)" : "(Salah)");
    }

    printf("\nTekan Enter untuk keluar...");
    getchar(); // Menunggu input sebelum program selesai
    return 0;
}
