#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

#include <QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QTimer>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class Viewer;
struct Clip;
struct MediaStream;
class QOpenGLFramebufferObject;

class ViewerWidget : public QOpenGLWidget
{
	Q_OBJECT
public:
	ViewerWidget(QWidget *parent = 0);

    void paintGL();
    void initializeGL();
	Viewer* viewer;

	bool waveform;
	Clip* waveform_clip;
	MediaStream* waveform_ms;

	QOpenGLFramebufferObject* default_fbo;
protected:
    void paintEvent(QPaintEvent *e);
//    void resizeGL(int w, int h);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
private:
	QTimer retry_timer;
    void drawTitleSafeArea();
	bool dragging;
	void seek_from_click(int x);
	GLuint compose_sequence(Clip *nest, bool render_audio);
	GLuint draw_clip(QOpenGLFramebufferObject *clip, GLuint texture);
private slots:
	void retry();
    void deleteFunction();
};

#endif // VIEWERWIDGET_H
