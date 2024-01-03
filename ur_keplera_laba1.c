#include <stdio.h>
#include <math.h>

// Функция для решения уравнения методом итераций
double fixedPointIteration(double M, double e, double initial_guess, double tolerance, int max_iterations) {
    double E_prev = initial_guess; // Инициализация предыдущего значения эксцентрической аномалии
    double E_next; // Инициализация текущего значения эксцентрической аномалии
    
    for (int i = 0; i < max_iterations; i++) {
        // Вычисление нового значения эксцентрической аномалии по формуле
        E_next = E_prev + (M - E_prev + e * sin(E_prev)) / (1 - e * cos(E_prev));
        
        // Проверка условия сходимости
        if (fabs(E_next - E_prev) < tolerance) {
            return E_next; // Возвращаем найденное значение эксцентрической аномалии
        }
        
        E_prev = E_next; // Обновляем предыдущее значение эксцентрической аномалии
    }
    
    return -1; // Решение не было найдено
}

// Функция для решения уравнения методом половинного деления
double bisectionMethod(double M, double e, double initial_guess, double tolerance, int max_iterations) {
    double a = 0; // Нижняя граница интервала
    double b = M_PI; // Верхняя граница интервала
    
    for (int i = 0; i < max_iterations; i++) {
        double c = (a + b) / 2; // Середина интервала
        
        // Вычисление значений функции на концах и в середине интервала
        double fa = M - a + e * sin(a);
        double fb = M - b + e * sin(b);
        double fc = M - c + e * sin(c);
        
        // Проверка условия сходимости
        if (fabs(fc) < tolerance) {
            return c; // Возвращаем найденное значение эксцентрической аномалии
        }
        
        // Обновление границ интервала
        if (fa * fc < 0) {
            b = c;
        } else {
            a = c;
        }
    }
    
    return -1; // Решение не было найдено
}

// Функция для решения уравнения методом золотого сечения
double goldenSectionMethod(double M, double e, double initial_guess, double tolerance, int max_iterations) {
    double a = 0; // Нижняя граница интервала
    double b = M_PI; // Верхняя граница интервала
    
    double phi = (1 + sqrt(5)) / 2; // Золотое сечение
    
    for (int i = 0; i < max_iterations; i++) {
        double c = b - (b - a) / phi; // Значение внутренней точки интервала
        double d = a + (b - a) / phi; // Значение внешней точки интервала
        
        // Вычисление значений функции во внутренней и внешней точках интервала
        double fc = M - c + e * sin(c);
        double fd = M - d + e * sin(d);
        
        // Проверка условия сходимости
        if (fabs(fc) < tolerance) {
            return c; // Возвращаем найденное значение эксцентрической аномалии
        }
        
        // Обновление границ интервала
        if (fc < fd) {
            b = d;
        } else {
            a = c;
        }
    }
    
    return -1; // Решение не было найдено
}

// Функция для решения уравнения методом Ньютона
double newtonMethod(double M, double e, double initial_guess, double tolerance, int max_iterations) {
    double E_prev = initial_guess; // Инициализация предыдущего значения эксцентрической аномалии
    double E_next; // Инициализация текущего значения эксцентрической аномалии
    
    for (int i = 0; i < max_iterations; i++) {
        // Вычисление нового значения эксцентрической аномалии по формуле Ньютона
        E_next = E_prev - (E_prev - e * sin(E_prev) - M) / (1 - e * cos(E_prev));
        
        // Проверка условия сходимости
        if (fabs(E_next - E_prev) < tolerance) {
            return E_next; // Возвращаем найденное значение эксцентрической аномалии
        }
        
        E_prev = E_next; // Обновляем предыдущее значение эксцентрической аномалии
    }
    
    return -1; // Решение не было найдено
}

int main() {
    double M = 1.5; // Средняя аномалия
    double e = 0.5; // Эксцентриситет
    
    double initial_guess = 0; // Начальное приближение
    double tolerance = 1e-6; // Допустимая погрешность
    int max_iterations = 100; // Максимальное количество итераций
    
    // Решение уравнения методом итераций
    double result1 = fixedPointIteration(M, e, initial_guess, tolerance, max_iterations);
    printf("Fixed Point Iteration: %.6f\\n", result1);
    
    // Решение уравнения методом половинного деления
    double result2 = bisectionMethod(M, e, initial_guess, tolerance, max_iterations);
    printf("Bisection Method: %.6f\\n", result2);
    
    // Решение уравнения методом золотого сечения
    double result3 = goldenSectionMethod(M, e, initial_guess, tolerance, max_iterations);
    printf("Golden Section Method: %.6f\\n", result3);
    
    // Решение уравнения методом Ньютона
    double result4 = newtonMethod(M, e, initial_guess, tolerance, max_iterations);
    printf("Newton's Method: %.6f\\n", result4);
    
    return 0;
}