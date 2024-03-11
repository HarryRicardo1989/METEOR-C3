#include "kalman_filter.hpp"
/**
 * @brief Construct a new KalmanFilter::KalmanFilter object
 *
 * @param  q representa a covariância do ruído do processo,
 * ou seja, a incerteza associada com a mudança de estado do sistema.
 * Valores maiores de Q representam maior incerteza sobre a dinâmica do sistema, enquanto valores menores de Q representam menor incerteza,
 * Um valor maior para Q significa que o filtro responde mais rapidamente às mudanças no sistema, mas pode ser mais sensível a ruídos.
 *
 * @param  r  representa a covariância do ruído de medição,
 * ou seja, a incerteza associada com a medição do estado do sistema.
 * Valores maiores de R representam maior incerteza na medição, enquanto valores menores de R representam menor incerteza,
 * Um valor maior para R significa que o filtro confia mais nas medições, mas pode ser mais lento para se adaptar às mudanças no sistema..
 *
 * @param  p representa a covariância estimada do erro de estado. No início,
 * P é inicializado como uma estimativa da incerteza do estado inicial do sistema.
 * Em cada iteração, P é atualizado com base na estimativa do estado atual e na covariância do ruído do processo.
 * Valores maiores de P representam maior incerteza na estimativa do estado atual do sistema, enquanto valores menores de P representam menor incerteza,
 * Um valor maior para P significa que o filtro confia mais na estimativa inicial, mas pode ser mais lento para se adaptar às mudanças no sistema..
 */
namespace FILTER
{
    KalmanFilter::KalmanFilter(float q, float r, float p)
    {
        x_est = 0.0; // estimativa do estado atual
        P_est = p;   // estimativa da incerteza do estado atual
        Q = q;       // covariância do ruído do processo
        R = r;       // covariância do ruído da medição
    }

    int KalmanFilter::filter(float measurement)
    {
        // Variáveis temporárias
        float K;
        float P_pred;
        float x_pred;

        // Predição do estado atual
        x_pred = x_est;
        P_pred = P_est + Q;

        // Cálculo do ganho de Kalman
        K = P_pred / (P_pred + R);

        // Correção da estimativa do estado atual
        x_est = x_pred + K * (measurement - x_pred);

        // Atualização da incerteza do estado atual
        P_est = (1 - K) * P_pred;

        // Retorno da leitura filtrada
        return (int)x_est;
    }
    void KalmanFilter::updateStatus(float status)
    {
        // Atualização do estado atual
        x_est = status;

        // Atualização da incerteza do estado atual
        P_est = P_est + Q;
    }
}