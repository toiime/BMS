#include "Speech/Speech.h"

Speech::Speech(QWidget* parent) : QWidget(parent) {
	_speech = new QTextToSpeech(this);
}

Speech::~Speech() {
	if (_speech) {
		delete _speech;
		_speech = nullptr;
	}
}

void Speech::Say(const QString& content) {
	_speech->say(content);
}