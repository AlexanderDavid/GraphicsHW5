#include <iostream>
#include <stdexcept>

#include <Eigen/Dense>

int main(int argv, char** argc)
{
    if (argv != 4)
    {
        std::cerr << "Usage: " << argc[0] << " [Point2X] [Point2Y] [Point2Z]\n";
        return -1;
    }

    auto p0 = Eigen::Vector3d{0, 0, 0};
    auto p2 = Eigen::Vector3d{0, 0, 0};
    auto alpha = Eigen::Vector3d{0, 0, 1};
    auto l0 = 2.5;
    auto l1 = 1.5;

    try 
    {
        p2 = Eigen::Vector3d{
            std::stod(argc[1]),
            std::stod(argc[2]),
            std::stod(argc[3])
        };
    }
    catch (const std::invalid_argument&)
    {
        std::cerr << "Please enter valid numeric values for the x, y, and z values of point2\n";
        return -2;
    }

    double theta = std::acos(((p2 - p0).squaredNorm() - std::pow(l0, 2) - std::pow(l1, 2)) /
                                (2 * l0 * l1));

    if (std::isnan(theta))
    {
        std::cerr << "Value for P2 makes theta invalid \n theta = ";
        std::cerr << ((p2 - p0).squaredNorm() - std::pow(l0, 2) - std::pow(l1, 2)) /
                                (2 * l0 * l1);
        std::cerr << "\n";
        return -3;
    }

    double phi = std::acos(((p2 - p0).norm()) /
                           (l0 + l1 * std::cos(theta)));

    if (std::isnan(phi))
    {
        std::cerr << "Value for P2 makes phi invalid...\n theta = ";
        std::cerr << ((p2 - p0).squaredNorm() - std::pow(l0, 2) - std::pow(l1, 2)) /
        std::cerr << "\nphi =";
                                (2 * l0 * l1);
        std::cerr << ((p2 - p0).norm()) / (l0 + l1 * std::cos(theta));
        std::cerr << "\n";

        return -3;
    }

    auto xHat = (p2 - p0).normalized();

    auto n0 = xHat * std::cos(phi) + (alpha.cross(xHat) * std::sin(phi));
    auto n1 = n0 * std::cos(theta) + (alpha.cross(n0) * std::sin(theta));

    auto p1 = p0 + (n0 * l0);

    std::cout << "The value of p1 that makes the system consistent is:\n" <<
                 "X: " << p1.x() << "\n" <<
                 "Y: " << p1.y() << "\n" <<
                 "Z: " << p1.z() << "\n";

    auto p2Check = p0 + (n0 * l0) + (n1 * l1);

    std::cout << "The value of p2 that results (sanity check):\n" <<
                 "X: " << p2.x() << "\n" <<
                 "Y: " << p2.y() << "\n" <<
                 "Z: " << p2.z() << "\n";

    return 0;
}
