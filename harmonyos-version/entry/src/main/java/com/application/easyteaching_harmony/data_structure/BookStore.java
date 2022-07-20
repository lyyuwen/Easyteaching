package com.application.easyteaching_harmony.data_structure;

import ohos.data.orm.OrmDatabase;
import ohos.data.orm.annotation.Database;

@Database(entities = {Users.class}, version = 1)
public abstract class BookStore extends OrmDatabase {

}
