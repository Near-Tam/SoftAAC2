/*
* Copyright (C) 2012 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

//#define LOG_NDEBUG 0
#define LOG_TAG "Softlame"
#include <utils/Log.h>

#include "Softlame.h"

#include <media/stagefright/foundation/ADebug.h>

namespace android{
template<class T>
static void InitOMXParams(T *params){
    params->nSize = sizeof(T);
    params->nVersion.s.nVersionMajor = 1;
    params->nVersion.s.nVersionMinor = 0;
    params->nVersion.s.nRevision = 0;
    params->nVersion.s.nStep = 0;
}

Softlame::Softlame(/*input params*/)
    : SimpleSoftOMXComponent(name, callbacks, appData, component),
      /*init params and funtion*/
      /*like this:            */
      /*mAACDecoder(NULL),   */
      /*mIsADTS(false),     */
      {
          /*funtion*/
          ALOGE("zhiyuanLOG");
          initPorts();
          /*and other*/
      }


void Softlame::initPorts() {
    OMX_PARAM_PORTDEFINITIONTYPE def;
    InitOMXParams(&def);

    def.nPortIndex = 0;
    def.eDir = OMX_DirInput;
    def.nBufferCountMin = kNumInputBuffers;
    def.nBufferCountActual = def.nBufferCountMin;
    def.nBufferSize = 8192;
    def.bEnabled = OMX_TRUE;
    def.bPopulated = OMX_FALSE;
    def.eDomain = OMX_PortDomainAudio;
    def.bBuffersContiguous = OMX_FALSE;
    def.nBufferAlignment = 1;

    def.format.audio.cMIMEType = const_cast<char *>("audio/aac");
    def.format.audio.pNativeRender = NULL;
    def.format.audio.bFlagErrorConcealment = OMX_FALSE;
    def.format.audio.eEncoding = OMX_AUDIO_CodingAAC;

    addPort(def);

    def.nPortIndex = 1;
    def.eDir = OMX_DirOutput;
    def.nBufferCountMin = kNumOutputBuffers;
    def.nBufferCountActual = def.nBufferCountMin;
    def.nBufferSize = 4096 * MAX_CHANNEL_COUNT;
    def.bEnabled = OMX_TRUE;
    def.bPopulated = OMX_FALSE;
    def.eDomain = OMX_PortDomainAudio;
    def.bBuffersContiguous = OMX_FALSE;
    def.nBufferAlignment = 2;

    def.format.audio.cMIMEType = const_cast<char *>("audio/raw");
    def.format.audio.pNativeRender = NULL;
    def.format.audio.bFlagErrorConcealment = OMX_FALSE;
    def.format.audio.eEncoding = OMX_AUDIO_CodingPCM;

    addPort(def);
}

OMX_ERRORTYPE Softlame::internalGetParameter(
        OMX_INDEXTYPE index, OMX_PTR params){
    switch (index){
        case /*OMX_....1*/ :
        {
            /*...*/
            return OMX_ErrorNone;
        }

        case /*OMX_....2*/ :
        {
            /*...*/
            return OMX_ErrorNone;
        }
        
        default:
            return SimpleSoftOMXComponent::internalSetParameter(index, params);

    }            

    
}

OMX_ERRORTYPE Softlame::internalSetParameter(
        OMX_INDEXTYPE index, const OMX_PTR params){
    switch(index){
        case /*OMX_...1*/ :
        {
            /*...*/
            return OMX_ErrorNone;
        }
        case /*OMX_...2*/ :
        {
            /*...*/
            return OMX_ErrorNone;
        }
        default:
            return SimpleSoftOMXComponent::internalSetParameter(index, params);
    }
}
void Softlame::onQueueFilled(OMX_U32 /* portIndex*/){
    if (mSignalledError || mOutputPorSettingsChange != NONE){
        return;
    }

    List<BufferInfo *> &inQueue = getPortQueue(0);
    List<BufferInfo *> &outQueue = getPortQueue(1);

    while((!inQueue.empty() || mEndOfInput) && !outQueue.empty()){
        
    }
}

void Softlame::onPortFlushCompleted(OMX_U32 portIndex){
    if(portIndex == 0){

    }
}

void Softlame::onPortEnableCompleted(OMX_U32 portIndex, bool enabled){
    if (portIndex != 1){
        return;
    }
    switch (mOutputPortSettingsChange){
        case NONE:
            break;
        case AWAITING_DISABLED:
        {
            CHECK(!enabled);
            mOutputPortSettingsChange = AWAITING_ENABLED;
            break;
        }
        default:
        {
            CHECK_EQ(()mOutputPortSettingsChange, (int)AWAITING_ENABLED);
            CHECK(enabled);
            mOutputPortSettingsChange = NONE;
            break;
        }
    }
}

void Softlame::onReset(){
    /* Reset the "configured" state*/

}

} // namespace android

android::SoftOMXCommponent *createSoftOMXComponent(
        const char *name, const OMX_CALLBACKTYPE *callback,
        OMX_PTR appData, OMX_COMPONENTTYPE **component){
            return new anndroid::Softlame(name,callbacks,appData,component);
        }

