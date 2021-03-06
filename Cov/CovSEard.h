#pragma once
#include "Cov.h"
class CovSEard : public Cov
{
public:
    explicit CovSEard(size_t d);
    size_t num_hyp() const;
    Eigen::MatrixXd k(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x1, const Eigen::MatrixXd& x2) const;
    Eigen::MatrixXd dk_dhyp(const Eigen::VectorXd& hyp, size_t idx, const Eigen::MatrixXd& x1, const Eigen::MatrixXd& x2) const;
    Eigen::MatrixXd dk_dhyp(const Eigen::VectorXd& hyp, size_t idx, const Eigen::MatrixXd& x1, const Eigen::MatrixXd& x2, const Eigen::MatrixXd& K) const;
    Eigen::MatrixXd dk_dx1(const Eigen::VectorXd&  hyp, const Eigen::VectorXd& x1, const Eigen::MatrixXd& x2) const;
    Eigen::MatrixXd dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1, const Eigen::MatrixXd& x2, const Eigen::RowVectorXd& K) const;

    std::pair<Eigen::VectorXd, Eigen::VectorXd> cov_hyp_range(const Eigen::MatrixXd& xs, const Eigen::VectorXd& ys) const;
    Eigen::VectorXd default_hyp(const Eigen::MatrixXd& xs, const Eigen::VectorXd& ys) const;

    Eigen::VectorXd diag_k(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x) const;
    Eigen::MatrixXd diag_dk_dhyp(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x) const;
    Eigen::MatrixXd diag_dk_dhyp(const Eigen::VectorXd& hyp, const Eigen::MatrixXd& x, const Eigen::MatrixXd& K) const;
    Eigen::MatrixXd diag_dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1) const;
    Eigen::MatrixXd diag_dk_dx1(const Eigen::VectorXd& hyp, const Eigen::VectorXd& x1, const Eigen::RowVectorXd& K) const;
};
