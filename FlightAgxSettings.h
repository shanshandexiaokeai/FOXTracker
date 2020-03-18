#ifndef FLIGHTAGXSETTINGS_H
#define FLIGHTAGXSETTINGS_H
#include <opencv2/opencv.hpp>
#include <Eigen/Eigen>
#include <opencv2/core/eigen.hpp>
#include <chrono>
#include <QApplication>
#include <QDebug>

class FlightAgxSettings {
public:
    cv::Mat K;
    cv::Mat D;
    int detect_duration = 10;
    bool enable_preview = true;
    int camera_id = 0;
    bool enable_multithread_detect = true;
    int retrack_queue_size = 1;
    double fps = 30;
    bool send_posedata_udp = true;
    int port = 4242;
    std::string udp_host = "127.0.0.1";

    std::string trackir_path = "/assets/TrackIR.exe";
    std::string support_games_csv = "/assets/facetracknoir supported games.csv";
    std::string model = "/assets/model.txt";
    std::string landmark_model = "/assets/shape_predictor_68_face_landmarks.dat";

    bool use_ft = true;
    bool use_npclient = true;
    double cov_Q = 0.2;
    double cov_T = 0.03;

    double cov_V = 0.1;
    double cov_W = 0.02;

    double ekf_predict_dt = 0.01;

    FlightAgxSettings() {
        Eigen::Matrix3d K_eigen;
        Eigen::VectorXd D_eigen(5);
        K_eigen << 520.70925933,   0.,         319.58341522,
                  0.,         520.3492704,  231.99546224,
                  0.,           0.,           1.   ;
        D_eigen << 0.19808774, -0.68766424, -0.00180889,  0.0008008 ,  0.7539345;
        cv::eigen2cv(K_eigen, K);
        D_eigen = D_eigen.transpose();
        cv::eigen2cv(D_eigen, D);

        std::string app_path = QCoreApplication::applicationDirPath().toStdString();
        trackir_path = app_path + trackir_path;
        support_games_csv = app_path + support_games_csv;
        model = app_path + model;
        landmark_model = app_path + landmark_model;
        qDebug() << "App run at" << app_path.c_str();

    }
};


class TicToc
{
  public:
    TicToc()
    {
        tic();
    }

    void tic()
    {
        start = std::chrono::system_clock::now();
    }

    double toc()
    {
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        return elapsed_seconds.count() * 1000;
    }

  private:
    std::chrono::time_point<std::chrono::system_clock> start, end;
};

extern FlightAgxSettings * settings;
#endif // FLIGHTAGXSETTINGS_H
