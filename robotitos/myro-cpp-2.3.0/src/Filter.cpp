#include "Filter.h"

Filter::Filter(){
}

Filter::~Filter() {
}

void Filter::applyFilter(PicturePtr image) {
	this->filter(image);
}

void Filter::filter(PicturePtr image) {
	return;
}
