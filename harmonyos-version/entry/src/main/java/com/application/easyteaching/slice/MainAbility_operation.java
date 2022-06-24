package com.application.easyteaching.slice;

import com.application.easyteaching.slice.slice.MainAbility_operationSlice;
import ohos.aafwk.ability.Ability;
import ohos.aafwk.content.Intent;

public class MainAbility_operation extends Ability {
    @Override
    public void onStart(Intent intent) {
        super.onStart(intent);
        super.setMainRoute(MainAbility_operationSlice.class.getName());
    }
}
