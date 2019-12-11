#ifndef SPEECH_H_
#define SPEECH_H_

#include <QWidget>
#include <QTextToSpeech>

// 语音功能...
class Speech : public QWidget {
public:
	Speech(QWidget* parent = nullptr);
	~Speech();

public:
	void Say(const QString& content);

private:
	QTextToSpeech* _speech;
};

#endif // !SPEECH_H_