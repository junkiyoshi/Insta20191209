#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->mesh.clear();

	int span = 10;
	for (int x = -600; x <= 600; x += span) {

		for (int y = -600; y <= 600; y += span) {

			for (int i = 0; i < 2; i++) {

				if (i == 0) {
				
					this->mesh.addVertex(glm::vec3(x - span * 0.5, y - span * 0.5, 0));
					this->mesh.addVertex(glm::vec3(x + span * 0.5, y - span * 0.5, 0));
					this->mesh.addVertex(glm::vec3(x - span * 0.5, y + span * 0.5, 0));
				}
				else {

					this->mesh.addVertex(glm::vec3(x + span * 0.5, y - span * 0.5, 0));
					this->mesh.addVertex(glm::vec3(x + span * 0.5, y + span * 0.5, 0));
					this->mesh.addVertex(glm::vec3(x - span * 0.5, y + span * 0.5, 0));
				}

				int index = mesh.getNumVertices() - 3;
				auto avg = (mesh.getVertex(index) + mesh.getVertex(index + 1) + mesh.getVertex(index + 2)) / 3;
				auto z = 0;
				auto noise_value = ofNoise(glm::vec4(avg * 0.01, ofGetFrameNum() * 0.005));
				if (noise_value > 0.65) {

					z = ofMap(noise_value, 0.65, 1, 0, 300);
				}

				auto angle_x = ofMap(z, 0, 300, 0, PI * 10);
				auto angle_y = ofMap(z, 0, 300, 0, PI * 10);
				auto angle_z = ofMap(z, 0, 300, 0, PI * 10);

				auto rotation_x = glm::rotate(glm::mat4(), angle_x, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), angle_y, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), angle_z, glm::vec3(0, 0, 1));

				for (int k = index; k < this->mesh.getNumVertices(); k++) {

					auto vertex = this->mesh.getVertex(k);
					vertex -= avg;
					vertex = glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
					vertex += avg + glm::vec3(0, 0, z);
					this->mesh.setVertex(k, vertex);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(39);
	this->mesh.drawFaces();

	ofSetColor(239);
	this->mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}