#ifndef GLDRAWER_H
#define GLDRAWER_H

#include <QGLWidget>
#include <QMouseEvent>
#include <map>

class EmbPymol;

class GLDrawer : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDrawer(QWidget *parent = 0, QGLFormat *format = 0, int finalize = 0);
    ~GLDrawer();
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

signals:
    
public slots:
    void _pymolProcess();
    void loadFile(std::string *fname);
    void render(bool enable, std::string type);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    EmbPymol *embPymol;

    std::map<int, int> _buttonMap;

//    [("All Readable","*.pdb"),
//                   ("All Readable","*.pdb1"),
//                   ("All Readable","*.ccp4"),
//                   ("All Readable","*.xplor"),
//                   ("All Readable","*.mol"),
//                   ("All Readable","*.mol2"),
//                   ("All Readable","*.sdf"),
//                   ("All Readable","*.xyz"),
//                   ("All Readable","*.r3d"),
//                   ("All Readable","*.cc1"),
//                   ("All Readable","*.cc2"),
//                   ("All Readable","*.ent"),
//                   ("All Readable","*.dat"),
//                   ("All Readable","*.out"),
//                   ("All Readable","*.mmd"),
//                   ("All Readable","*.mmod"),
//                   ("All Readable","*.pse"),
//                   ("All Readable","*.psw"),
//                   ("All Readable","*.phi"),
//                   ("All Readable","*.fld"),
//                   ("All Readable","*.grd"),
//                   ("All Readable","*.o"),
//                   ("All Readable","*.omap"),
//                   ("All Readable","*.brix"),
//                   ("All Readable","*.dx"),
//                   ("All Readable","*.pqr"),
//                   ("All Readable","*.p5m"),
//                   ("All Readable","*.p1m"),
//                   ("All Readable","*.cube"),
//                   ("All Readable","*.cif"),
//                   ("All Readable","*.moe"), # proprietary format
//                   ("All Readable","*.mae"), # proprietary format
//                   ("All Readable","*.fasta"),
//                   ("All Readable","*.aln"),
//                   ("All Readable","*.acnt"),
//                   #("All Readable","*.mtz"),
//                   ("PDB File","*.pdb"),
//                   ("PDB1 File","*.pdb1"),
//                   ("All Files","*.*"),
//                   ("All Files","*"),
//                   ("PDB File","*.ent"),
//                   ("PyMOL Session","*.pse"),
//                   ("PyMOL Show","*.psw"),
//                   ("CCP4 Map","*.ccp4"),
//                   ("XPLOR Map","*.xplor"),
//                   ("MOL2/Multi-MOL2","*.mol2"),
//                   ("Macromodel File","*.dat"),
//                   ("Macromodel File","*.out"),
//                   ("Macromodel File","*.mmd"),
//                   ("Macromodel File","*.mmod"),
//   #                ("MTZ Reflection File","*.mtz"),
//                   ("BRIX/O Map","*.o"),
//                   ("BRIX/O Map","*.omap"),
//                   ("BRIX/O Map","*.brix"),
//                   ("CIF","*.cif"),
//                   ("Gaussian Cube Map","*.cube"),
//                   ("DX Map","*.dx"),
//                   ("AVS (MEAD) Field","*.fld"),
//                   ("MOL File","*.mol"),
//                   ("MOE File","*.moe"), # proprietary format
//                   ("MAE File","*.mae"), # proprietary format
//                   ("ChemPy Model","*.pkl"),
//                   ("Raster3D Scene","*.r3d"),
//                   ("SDF File","*.sdf"),
//                   ("ChemDraw3D File","*.cc1"),
//                   ("ChemDraw3D File","*.cc2"),
//                   ("XYZ File","*.xyz"),
//                   ("Fasta File","*.fasta"),
//                   ("CLUSTAL file","*.aln"),
//                   ("ACNT Map","*.acnt"),
};

#endif // GLDRAWER_H
