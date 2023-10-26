#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetColor(255);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int deg = 0; deg < 360; deg += 5) {

		auto noise_location = glm::vec2(250 * cos(deg * DEG_TO_RAD), 250 * sin(deg * DEG_TO_RAD));

		auto base_1 = glm::vec2(320 * cos(deg * DEG_TO_RAD), 320 * sin(deg * DEG_TO_RAD));
		auto target_radius_1 = ofMap(ofNoise(glm::vec3(noise_location * 0.085, ofGetFrameNum() * 0.03)), 0, 1, 250, 320);
		auto target_1 = glm::vec2(target_radius_1 * cos(deg * DEG_TO_RAD), target_radius_1 * sin(deg * DEG_TO_RAD));

		auto base_2 = glm::vec2(180 * cos(deg * DEG_TO_RAD), 180 * sin(deg * DEG_TO_RAD));
		auto target_radius_2 = ofMap(ofNoise(glm::vec3(noise_location * 0.085, ofGetFrameNum() * 0.03)), 0, 1, 180, 250);
		auto target_2 = glm::vec2(target_radius_2 * cos(deg * DEG_TO_RAD), target_radius_2 * sin(deg * DEG_TO_RAD));

		this->draw_arrow(base_1, target_1, 12);
		this->draw_arrow(base_2, target_2, 12);

		auto target_radius = ofMap(ofNoise(glm::vec3(noise_location * 0.085, ofGetFrameNum() * 0.03)), 0, 1, 225, 275);
		auto target = glm::vec2(target_radius * cos(deg * DEG_TO_RAD), target_radius * sin(deg * DEG_TO_RAD));

		ofDrawCircle(target, 3);
	}
}

//--------------------------------------------------------------
void ofApp::draw_arrow(glm::vec2 location, glm::vec2 target, float size) {

	auto angle = std::atan2(target.y - location.y, target.x - location.x);
	auto distance = glm::distance(target, location);

	ofPushMatrix();
	ofTranslate(target);

	ofFill();
	ofBeginShape();
	ofVertex(glm::vec2(size * cos(angle), size * sin(angle)));
	ofVertex(glm::vec2(size * 0.35 * cos(angle + PI * 0.5), size * 0.35 * sin(angle + PI * 0.5)));
	ofVertex(glm::vec2(size * 0.35 * cos(angle - PI * 0.5), size * 0.35 * sin(angle - PI * 0.5)));
	ofEndShape();

	ofBeginShape();
	ofVertex(glm::vec2(size * 0.35 * cos(angle + PI * 0.5), size * 0.35 * sin(angle + PI * 0.5)) * 0.5);
	ofVertex(glm::vec2(size * 0.35 * cos(angle + PI * 0.5), size * 0.35 * sin(angle + PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.35 * cos(angle - PI * 0.5), size * 0.35 * sin(angle - PI * 0.5)) * 0.5 - glm::vec2(distance * cos(angle), distance * sin(angle)));
	ofVertex(glm::vec2(size * 0.35 * cos(angle - PI * 0.5), size * 0.35 * sin(angle - PI * 0.5)) * 0.5);
	ofEndShape();

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}