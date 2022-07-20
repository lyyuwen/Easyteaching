package com.application.easyteaching_harmony;

import com.application.easyteaching_harmony.slice.ToolsSlice_for_login;
import ohos.aafwk.ability.Ability;
import ohos.aafwk.content.Intent;

public class Tools extends Ability {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setMainRoute(ToolsSlice_for_login.class.getName());
    }
}
