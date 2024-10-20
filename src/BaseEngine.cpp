#include "BaseEngine.h"

#include "ofAppBaseWindow.h"
#include "ofAppRunner.h"
#include "imgui.h"

namespace ofxImGui
{
int BaseEngine::g_ShaderHandle = 0;
int BaseEngine::g_VertHandle = 0;
int BaseEngine::g_FragHandle = 0;

int BaseEngine::g_UniformLocationTex = 0;
int BaseEngine::g_UniformLocationProjMtx = 0;
int BaseEngine::g_AttribLocationUV = 0;
int BaseEngine::g_AttribLocationPosition = 0;
int BaseEngine::g_AttribLocationColor = 0;

unsigned int BaseEngine::g_VboHandle = 0;
unsigned int BaseEngine::g_VaoHandle = 0;
unsigned int BaseEngine::g_ElementsHandle = 0;

std::string BaseEngine::g_ClipboardText = "";

// Maps OF keys to ImGui keys
// Openframeworks keys are platform-specific
ImGuiKey BaseEngine::oFKeyToImGuiKey(int key)
{
    switch (key)
    {
    // Openframeworks keycodes are platform and windowing system dependant.
    // But there are some universal ones
    case OF_KEY_TAB:       return ImGuiKey_Tab;
    case OF_KEY_RETURN:    return ImGuiKey_Enter;
    case OF_KEY_ESC:       return ImGuiKey_Escape;
    case OF_KEY_BACKSPACE: return ImGuiKey_Backspace;
    case OF_KEY_DEL:       return ImGuiKey_Delete;
    case OF_KEY_F1:        return ImGuiKey_F1;
    case OF_KEY_F2:        return ImGuiKey_F2;
    case OF_KEY_F3:        return ImGuiKey_F3;
    case OF_KEY_F4:        return ImGuiKey_F4;
    case OF_KEY_F5:        return ImGuiKey_F5;
    case OF_KEY_F6:        return ImGuiKey_F6;
    case OF_KEY_F7:        return ImGuiKey_F7;
    case OF_KEY_F8:        return ImGuiKey_F8;
    case OF_KEY_F9:        return ImGuiKey_F9;
    case OF_KEY_F10:       return ImGuiKey_F10;
    case OF_KEY_F11:       return ImGuiKey_F11;
    case OF_KEY_F12:       return ImGuiKey_F12;
    case OF_KEY_LEFT:      return ImGuiKey_LeftArrow;
    case OF_KEY_UP:        return ImGuiKey_UpArrow;
    case OF_KEY_RIGHT:     return ImGuiKey_RightArrow;
    case OF_KEY_DOWN:      return ImGuiKey_DownArrow;
    case OF_KEY_PAGE_UP:   return ImGuiKey_PageUp;
    case OF_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
    case OF_KEY_HOME:      return ImGuiKey_Home;
    case OF_KEY_END:       return ImGuiKey_End;
    case OF_KEY_INSERT:    return ImGuiKey_Insert;

#if defined (TARGET_GLFW_WINDOW)
    case GLFW_KEY_TAB: return ImGuiKey_Tab;
    case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
    case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
    case GLFW_KEY_UP: return ImGuiKey_UpArrow;
    case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
    case GLFW_KEY_PAGE_UP: return ImGuiKey_PageUp;
    case GLFW_KEY_PAGE_DOWN: return ImGuiKey_PageDown;
    case GLFW_KEY_HOME: return ImGuiKey_Home;
    case GLFW_KEY_END: return ImGuiKey_End;
    case GLFW_KEY_INSERT: return ImGuiKey_Insert;
    case GLFW_KEY_DELETE: return ImGuiKey_Delete;
    case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
    case GLFW_KEY_SPACE: return ImGuiKey_Space;
    case GLFW_KEY_ENTER: return ImGuiKey_Enter;
    case GLFW_KEY_ESCAPE: return ImGuiKey_Escape;
    case GLFW_KEY_APOSTROPHE: return ImGuiKey_Apostrophe;
    case GLFW_KEY_COMMA: return ImGuiKey_Comma;
    case GLFW_KEY_MINUS: return ImGuiKey_Minus;
    case GLFW_KEY_PERIOD: return ImGuiKey_Period;
    case GLFW_KEY_SLASH: return ImGuiKey_Slash;
    case GLFW_KEY_SEMICOLON: return ImGuiKey_Semicolon;
    case GLFW_KEY_EQUAL: return ImGuiKey_Equal;
    case GLFW_KEY_LEFT_BRACKET: return ImGuiKey_LeftBracket;
    case GLFW_KEY_BACKSLASH: return ImGuiKey_Backslash;
    case GLFW_KEY_RIGHT_BRACKET: return ImGuiKey_RightBracket;
    case GLFW_KEY_GRAVE_ACCENT: return ImGuiKey_GraveAccent;
    case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
    case GLFW_KEY_SCROLL_LOCK: return ImGuiKey_ScrollLock;
    case GLFW_KEY_NUM_LOCK: return ImGuiKey_NumLock;
    case GLFW_KEY_PRINT_SCREEN: return ImGuiKey_PrintScreen;
    case GLFW_KEY_PAUSE: return ImGuiKey_Pause;
    case GLFW_KEY_KP_0: return ImGuiKey_Keypad0;
    case GLFW_KEY_KP_1: return ImGuiKey_Keypad1;
    case GLFW_KEY_KP_2: return ImGuiKey_Keypad2;
    case GLFW_KEY_KP_3: return ImGuiKey_Keypad3;
    case GLFW_KEY_KP_4: return ImGuiKey_Keypad4;
    case GLFW_KEY_KP_5: return ImGuiKey_Keypad5;
    case GLFW_KEY_KP_6: return ImGuiKey_Keypad6;
    case GLFW_KEY_KP_7: return ImGuiKey_Keypad7;
    case GLFW_KEY_KP_8: return ImGuiKey_Keypad8;
    case GLFW_KEY_KP_9: return ImGuiKey_Keypad9;
    case GLFW_KEY_KP_DECIMAL: return ImGuiKey_KeypadDecimal;
    case GLFW_KEY_KP_DIVIDE: return ImGuiKey_KeypadDivide;
    case GLFW_KEY_KP_MULTIPLY: return ImGuiKey_KeypadMultiply;
    case GLFW_KEY_KP_SUBTRACT: return ImGuiKey_KeypadSubtract;
    case GLFW_KEY_KP_ADD: return ImGuiKey_KeypadAdd;
    case GLFW_KEY_KP_ENTER: return ImGuiKey_KeypadEnter;
    case GLFW_KEY_KP_EQUAL: return ImGuiKey_KeypadEqual;
    case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
    case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
    case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
    case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
    case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
    case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
    case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
    case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
    case GLFW_KEY_MENU: return ImGuiKey_Menu;
    case GLFW_KEY_0: return ImGuiKey_0;
    case GLFW_KEY_1: return ImGuiKey_1;
    case GLFW_KEY_2: return ImGuiKey_2;
    case GLFW_KEY_3: return ImGuiKey_3;
    case GLFW_KEY_4: return ImGuiKey_4;
    case GLFW_KEY_5: return ImGuiKey_5;
    case GLFW_KEY_6: return ImGuiKey_6;
    case GLFW_KEY_7: return ImGuiKey_7;
    case GLFW_KEY_8: return ImGuiKey_8;
    case GLFW_KEY_9: return ImGuiKey_9;
    case GLFW_KEY_A: return ImGuiKey_A;
    case GLFW_KEY_B: return ImGuiKey_B;
    case GLFW_KEY_C: return ImGuiKey_C;
    case GLFW_KEY_D: return ImGuiKey_D;
    case GLFW_KEY_E: return ImGuiKey_E;
    case GLFW_KEY_F: return ImGuiKey_F;
    case GLFW_KEY_G: return ImGuiKey_G;
    case GLFW_KEY_H: return ImGuiKey_H;
    case GLFW_KEY_I: return ImGuiKey_I;
    case GLFW_KEY_J: return ImGuiKey_J;
    case GLFW_KEY_K: return ImGuiKey_K;
    case GLFW_KEY_L: return ImGuiKey_L;
    case GLFW_KEY_M: return ImGuiKey_M;
    case GLFW_KEY_N: return ImGuiKey_N;
    case GLFW_KEY_O: return ImGuiKey_O;
    case GLFW_KEY_P: return ImGuiKey_P;
    case GLFW_KEY_Q: return ImGuiKey_Q;
    case GLFW_KEY_R: return ImGuiKey_R;
    case GLFW_KEY_S: return ImGuiKey_S;
    case GLFW_KEY_T: return ImGuiKey_T;
    case GLFW_KEY_U: return ImGuiKey_U;
    case GLFW_KEY_V: return ImGuiKey_V;
    case GLFW_KEY_W: return ImGuiKey_W;
    case GLFW_KEY_X: return ImGuiKey_X;
    case GLFW_KEY_Y: return ImGuiKey_Y;
    case GLFW_KEY_Z: return ImGuiKey_Z;
    case GLFW_KEY_F1: return ImGuiKey_F1;
    case GLFW_KEY_F2: return ImGuiKey_F2;
    case GLFW_KEY_F3: return ImGuiKey_F3;
    case GLFW_KEY_F4: return ImGuiKey_F4;
    case GLFW_KEY_F5: return ImGuiKey_F5;
    case GLFW_KEY_F6: return ImGuiKey_F6;
    case GLFW_KEY_F7: return ImGuiKey_F7;
    case GLFW_KEY_F8: return ImGuiKey_F8;
    case GLFW_KEY_F9: return ImGuiKey_F9;
    case GLFW_KEY_F10: return ImGuiKey_F10;
    case GLFW_KEY_F11: return ImGuiKey_F11;
    case GLFW_KEY_F12: return ImGuiKey_F12;
#endif
    default: return ImGuiKey_None;
    }

    return ImGuiKey_None;
}

//--------------------------------------------------------------
void BaseEngine::onKeyEvent(ofKeyEventArgs& event)
{
    // This one is a little too ahrd to port, let's behave like EngineOpenFrameworks
    // ImGui_ImplGlfw_KeyCallback((GLFWwindow*)ofGetWindowPtr()->getWindowContext(), ...);

    int key = event.keycode; // Todo: this seems to be window specific ?
    ImGuiIO& io = ImGui::GetIO();

    // Set key modifiers (ensures they are set on time, fixes kb shortcuts)
    io.AddKeyEvent(ImGuiMod_Ctrl,  event.hasModifier(OF_KEY_CONTROL));
    io.AddKeyEvent(ImGuiMod_Shift, event.hasModifier(OF_KEY_SHIFT));
    io.AddKeyEvent(ImGuiMod_Alt,   event.hasModifier(OF_KEY_ALT));
    io.AddKeyEvent(ImGuiMod_Super, event.hasModifier(OF_KEY_SUPER));

    // Since 1.87 : Key events
    ImGuiKey imKey = oFKeyToImGuiKey(event.key);
    //ImGuiKey imgui_key = ImGui_ImplGlfw_KeyToImGuiKey(keycode); // Previous code

    // Fallback by guessing the imguikey from the typed character
    // Note: could create weird behaviour on some special keyboards ?
    // If so: It could be disabled, it doesn't prevent from using ImGui
    // This helps registering key up/down state, which is rarely used in imgui widgets.
    //		if(imKey == ImGuiKey_None){
    //			// Note: codepoint corresponds to the typed character
    //			imKey = keyCodeToImGuiKey( event.codepoint );
    //		}

    io.AddKeyEvent(imKey, event.type == ofKeyEventArgs::Pressed );

    // Note: this brings support for pre-1.87 user code using very specific API code.
    // It causes an assert/crash in imgui v1.89.3 when releasing ALT+CMD simultanously (osx+backend_of_native), when IMGUI_DISABLE_OBSOLETE_KEYIO is not defined.
    // As we disabled it, we can support old user code again.
    io.SetKeyEventNativeData(imKey, key, event.scancode); // To support legacy indexing (<1.87 user code)
}

//--------------------------------------------------------------
void BaseEngine::onMouseDragged(ofMouseEventArgs& event)
{

}

//--------------------------------------------------------------
void BaseEngine::onMousePressed(ofMouseEventArgs& event)
{
#ifdef TARGET_OF_IOS
    if (event.button == 0){ //on ios, only 1st finger reaches imgui
#else
    if (event.button >= 0 && event.button < 5){
#endif
        mousePressed[event.button] = true;
    }
}

//--------------------------------------------------------------
void BaseEngine::onMouseReleased(ofMouseEventArgs& event)
{
#ifdef TARGET_OF_IOS
    if (event.button == 0){ //on ios, only 1st finger reaches imgui
#else
    if (event.button >= 0 && event.button < 5){
#endif
        mousePressed[event.button] = false;
    }
}

//--------------------------------------------------------------
void BaseEngine::onMouseScrolled(ofMouseEventArgs& event)
{
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH = event.scrollX;
    io.MouseWheel = event.scrollY;
}

//--------------------------------------------------------------
void BaseEngine::onWindowResized(ofResizeEventArgs& window)
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2((float)window.width, (float)window.height);
}

//--------------------------------------------------------------
const char* BaseEngine::getClipboardString(ImGuiContext*)
{
    g_ClipboardText = ofGetWindowPtr()->getClipboardString();
    return g_ClipboardText.c_str();
}

//--------------------------------------------------------------
void BaseEngine::setClipboardString(ImGuiContext*, const char* text)
{
    g_ClipboardText = ofToString(text);
    ofGetWindowPtr()->setClipboardString(g_ClipboardText);
}

//--------------------------------------------------------------
GLuint BaseEngine::loadTextureImage2D(unsigned char * pixels, int width, int height)
{
    GLint last_texture;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);

    GLuint new_texture;
    glGenTextures(1, &new_texture);
    glBindTexture(GL_TEXTURE_2D, new_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width, height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                pixels
                );

    glBindTexture(GL_TEXTURE_2D, last_texture);

    return new_texture;
};
}
