#pragma once
#include <Eigen/Dense>
#include "../def.h"
#include "../util.h"
class Cov
{
protected:
    size_t _dim;

public:
    explicit Cov(size_t d) : _dim(d){}
    virtual ~Cov(){}
    virtual size_t num_hyp() const = 0;
    virtual Eigen::MatrixXd k(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x1, const Eigen::MatrixXd& x2) const = 0;
    virtual Eigen::MatrixXd dk_dhyp(const Eigen::VectorXd& hyp, size_t idx, const Eigen::MatrixXd& x1, const Eigen::MatrixXd& x2) const = 0;
    virtual Eigen::MatrixXd dk_dhyp(const Eigen::VectorXd& hyp, size_t idx, const Eigen::MatrixXd& x1, const Eigen::MatrixXd& x2, const Eigen::MatrixXd& K) const = 0;
    virtual Eigen::MatrixXd dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1, const Eigen::MatrixXd& x2) const = 0;
    virtual Eigen::MatrixXd dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1, const Eigen::MatrixXd& x2, const Eigen::RowVectorXd& K) const = 0;

    virtual std::pair<Eigen::VectorXd, Eigen::VectorXd> cov_hyp_range(const Eigen::MatrixXd& xs, const Eigen::VectorXd& ys) const = 0;
    virtual Eigen::VectorXd default_hyp(const Eigen::MatrixXd& xs, const Eigen::VectorXd& ys) const = 0;

    virtual Eigen::VectorXd diag_k(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x)       const = 0;
    virtual Eigen::MatrixXd diag_dk_dhyp(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x) const = 0;
    virtual Eigen::MatrixXd diag_dk_dhyp(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x, const Eigen::MatrixXd& K) const = 0;
    virtual Eigen::MatrixXd diag_dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1) const = 0;
    virtual Eigen::MatrixXd diag_dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1, const Eigen::RowVectorXd& K) const = 0;
};
