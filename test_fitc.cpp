#include "GP.h"
#include "FITC.h"
#include "util.h"
#include<Eigen/Dense>
#include<chrono>
#include<fstream>
#include<iomanip>
using namespace std;
using namespace Eigen;
using namespace std::chrono;
int main(int arg_num, char** args)
{
    cout << setprecision(9);
    const MatrixXd train_x = read_matrix("train_x").transpose();
    const VectorXd train_y = read_matrix("train_y");
    const MatrixXd test_x  = read_matrix("test_x").transpose();
    long num_train    = train_x.cols();
    long num_inducing = train_x.cols();
    if(arg_num > 1)
        num_train = atoi(args[1]);
    if(arg_num > 2)
        num_inducing = atoi(args[2]);

    if(num_train > train_x.cols())
    {
        cerr << "Num train > " << train_x.cols() << endl;
        exit(EXIT_FAILURE);
    }
    if(num_inducing > train_x.cols())
    {
        cerr << "Num test > " << train_x.cols() << endl;
        exit(EXIT_FAILURE);
    }

    FITC gp(train_x.leftCols(num_train), train_y.topRows(num_train), GP::CovFunc::COV_SE_ARD, GP::MatrixDecomp::QR);
    gp.set_inducing(train_x.rightCols(num_inducing));
    auto t1              = chrono::high_resolution_clock::now();
    double nlz           = gp.train(gp.get_default_hyps());
    auto t2              = chrono::high_resolution_clock::now();
    size_t training_time = duration_cast<chrono::seconds>(t2-t1).count();
    cout << "Training time: " << training_time << " seconds" << endl;
    cout << "Negative log likelihood: " << nlz << endl;
    cout << "Optimized hyperparameters:\n" << gp.get_hyp() << endl;
    gp.test_obj(gp.get_hyp());

    auto t3                = chrono::high_resolution_clock::now();
    VectorXd predy         = gp.batch_predict_y(test_x);
    VectorXd preds2        = gp.batch_predict_s2(test_x);
    auto t4                = chrono::high_resolution_clock::now();
    double prediction_time = 1e-6 * (double)(duration_cast<chrono::microseconds>(t4 - t3).count());
    cout << "Prediction time: " << prediction_time << " seconds" << endl;

    MatrixXd rec(test_x.cols(), 2);
    rec << predy, preds2.cwiseSqrt();

    ofstream f("pred");
    f << rec << endl;
    f.close();
    return EXIT_SUCCESS;
}
