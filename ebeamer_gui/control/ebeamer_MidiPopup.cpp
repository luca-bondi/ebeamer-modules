/*
  ==============================================================================

 Ebeamer GUI module
 Eventide Inc.
 Copyright Eventide Inc. 2021
 Author: Luca Bondi (bondi.luca@gmail.com)

  ==============================================================================
*/

namespace juce {

MidiPopup::MidiPopup(Component &o,MidiCC::Callback *cb, const String &param):owner(o){
    callback = cb;
    paramName = param;
}

bool MidiPopup::isLearning() const {
    return paramName == callback->getCCLearning();
}

void MidiPopup::showPopupMenu() {
    PopupMenu m;
    m.setLookAndFeel(&owner.getLookAndFeel());
    if (isLearning()) {
        m.addItem(1, "Stop learning CC", true, false);
    } else {
        m.addItem(1, "Learn CC", true, false);
    }

    auto mapping = callback->getParamToCCMapping();
    if (mapping.count(paramName) > 0) {
        m.addItem(2, "Forget CC ", true, false);
        m.addItem(3, "Chan: " + String(mapping[paramName].channel) + " - CC: " + String(mapping[paramName].number),
                  false, false);
    }

    if (popupArea.getX() == 0) {
        popupArea = PopupMenu::Options().getTargetScreenArea();
    }
    m.showMenuAsync(PopupMenu::Options().withTargetScreenArea(popupArea),
                    ModalCallbackFunction::create(sliderMenuCallback, this));

}

void MidiPopup::sliderMenuCallback(int result, MidiPopup *popup) {
    if (popup != nullptr) {
        switch (result) {
            case 1:
                if (!popup->isLearning()) {
                    popup->callback->removeCCParamMapping(popup->paramName);
                    popup->callback->startCCLearning(popup->paramName);
                    popup->showPopupMenu();
                } else {
                    popup->callback->stopCCLearning();
                    popup->popupArea.setBounds(0, 0, 0, 0);
                }
                break;
            case 2:
                popup->callback->removeCCParamMapping(popup->paramName);
                popup->popupArea.setBounds(0, 0, 0, 0);
                break;
            default:
                break;
        }
    }
}

} /* end namespace juce */
