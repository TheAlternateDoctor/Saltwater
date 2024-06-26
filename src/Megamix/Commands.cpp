#include <3ds.h>
#include <CTRPluginFramework.hpp>

#include "Megamix.hpp"

using CTRPluginFramework::OSD;
using CTRPluginFramework::Utils;

namespace Megamix{

    CSaveData* gSaveData = (CSaveData*)Region::GlobalSaveDataPointer();

    void tickflowCommandsHookWrapper() {
        asm(
            "mov r0, r6\n"
            "bl tickflowCommandsHook\n"
            "bx r0\n"
        );
    }

    extern "C" __attribute__((used)) 
    int tickflowCommandsHook(CTickflow* self, u32 cmd_num, u32 arg0, u32* args){
        switch(cmd_num){
            case 0: // Necessary, as it doesn't execute otherwise.
                return Region::TickflowAsyncSubLocation();
            case InputCheck:
                input_cmd(self, arg0, args);
            break;
            case VersionNumber:
                versionCheck(self, arg0, args);
            break;
        }
        return Region::TickflowCommandsEnd();
    }

    void input_cmd(CTickflow* self, u32 arg0, u32* args) {
            OSD::Notify("Current playstyle:"+Utils::ToString(gSaveData->mFileData[gSaveData->mCurrentFile].mPlayStyle));
        // if (arg0 > 2) {
        //     self->mCondvar = 0;
        //     return;
        // } else if (arg0 == 2) {
        //     // if you properly define the struct you can just do
        //     arg0 = gSaveData->mFileData[gSaveData->mCurrentFile].mPlayStyle;
        //     // otherwise you have to fuck with pointer arithmetic and i don't recommend it
        // }

        // if (arg0 == 0) {
        //     if (args[0] >= 32) {
        //         self->mCondvar = 0;
        //         return;
        //     }
            
        //     self->mCondvar = (gInputManager->unk4->unk4 >> args[0]) & 1;
        // } else {
        //     self->mCondvar = (gInputManager->unk8->unkC);
        // }
    }

    void versionCheck(CTickflow* self, u32 arg0, u32* args) {
                if (arg0 == 0){ //RHMPatch version
                    // OSD::Notify("RHMPatch version:"+SUPPORTED_RHMPATCH);
                    self->mCondvar = SUPPORTED_RHMPATCH;
                } else if (arg0 == 1){ //Saltwater version
                    // OSD::Notify("Saltwater version:"+VERSION_MAJOR*0x100+VERSION_MINOR);
                    self->mCondvar = VERSION_MAJOR*0x100+VERSION_MINOR;
                }
    }

}
