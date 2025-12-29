#include <sciplot/sciplot.hpp>
namespace sp = sciplot;
void plot2d(const std::vector<double> &y, std::string name){
    sp::Plot2D plot;
    std::vector<double> x_axis;
    for(int i = 0; i < y.size(); i++){
        x_axis.push_back((double)i);
    }
    std::valarray<double> vx(x_axis.data(), x_axis.size());
    std::valarray<double> vy(y.data(), y.size());
    plot.drawCurve(vx, vy);
    sciplot::Figure fig = {{plot}}; 
    sp::Canvas canvas = {{fig}};
    canvas.save(name + ".pdf");
}

void plot2d(const std::vector<double> &x, const std::vector<double> &y, std::string name){
    sp::Plot2D plot;
    std::valarray<double> vx(x.data(), x.size());
    std::valarray<double> vy(y.data(), y.size());
    plot.drawCurve(vx, vy);
    sciplot::Figure fig = {{plot}}; 
    sp::Canvas canvas = {{fig}};
    canvas.save(name + ".pdf");
}