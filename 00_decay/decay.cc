#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int N = 1000;
const float lambda = 1;
const float dt = 0.01;

void test_naive() {
    int n = N;
    float t = 0;
    FILE *fd = fopen("naive.dat", "w");
    while (n) {
        fprintf(fd, "%f %d\n", t, n);
        int delta_n = 0;
        for (int i = 0; i < n; i++) {
            float r = static_cast<float>(rand()) / RAND_MAX;
            if (r < lambda * dt) { ++delta_n; }
        }
        n -= delta_n;
        t += dt;
    }
    fclose(fd);
}

void test_ln() {
    float t = 0;
    int *steps = new int[N];
    int max_steps = 0;
    for (int i = 0; i < N; i++) {
        float r = static_cast<float>(rand()) / RAND_MAX;
        steps[i] = static_cast<int>(-log(r) / (lambda * dt)) + 1;
        if (steps[i] > max_steps) { max_steps = steps[i]; }
    }

    FILE *fd = fopen("ln.dat", "w");
    for (int s = 0; s < max_steps; s++) {
        int n = 0;
        for (int i = 0; i < N; i++) {
            if (steps[i] > s) { ++n; }
        }
        fprintf(fd, "%f %d\n", s * dt, n);
    }
    fclose(fd);
    delete [] steps;
}

int main(int argc, const char *argv[]) {
    srand(time(nullptr));
    test_naive();
    test_ln();
    return 0;
}
