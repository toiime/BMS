#include "Config/Config.h"

#include <QFile>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>

#include "Global/GlobalDefine.h"

Config* Config::_instance = new Config;
Config* Config::GetInstance() {
	return _instance;
}

Config::Config() {
	_configSpeech.powerState_ = 0;
	_configSpeech.volume_ = 50;
}

Config::~Config() {

}

void Config::LoadConfigFile() {
	QFile file(gConfigPath);
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::information(nullptr, QString("Note"), QString("%1 open error!").arg(gConfigPath));
		return;
	}

	QByteArray allData = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &jsonError));

	if (jsonError.error != QJsonParseError::NoError) {
		QMessageBox::information(nullptr, QString("Note"), QString("%1 error!").arg(gConfigPath));
		return;
	}

	QJsonObject rootObj = jsonDoc.object();

	if (rootObj.contains("Speech")) {
		QJsonObject speechObj = rootObj.value("Speech").toObject();
		if (speechObj.contains("powerState_"))
			_configSpeech.powerState_ = speechObj.value("powerState_").toInt();
		if (speechObj.contains("volume_"))
			_configSpeech.volume_ = speechObj.value("volume_").toInt();
		if (speechObj.contains("content_"))
			_configSpeech.content_ = speechObj.value("content_").toString();
	}
}

void Config::SaveConfigFile() {
	QFile file(gConfigPath);
	if (!file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
		QMessageBox::information(nullptr, QString("Note"), QString("%1 open error!").arg(gConfigPath));
		return;
	}

	QJsonObject jsonObjectSpeech;
	jsonObjectSpeech.insert("powerState_", _configSpeech.powerState_);
	jsonObjectSpeech.insert("volume_", _configSpeech.volume_);
	jsonObjectSpeech.insert("content_", _configSpeech.content_);

	QJsonObject jsonObjectRoot;
	jsonObjectRoot.insert("Speech", jsonObjectSpeech);

	QJsonDocument jsonDocument;
	jsonDocument.setObject(jsonObjectRoot);

	file.write(jsonDocument.toJson());
	file.close();
}

void Config::SetConfigSpeech(ConfigSpeech configSpeech) {
	_configSpeech = configSpeech;
}

Config::ConfigSpeech Config::GetConfigSpeech() {
	return _configSpeech;
}