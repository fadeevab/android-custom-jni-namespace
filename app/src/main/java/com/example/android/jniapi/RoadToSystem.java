package com.example.android.jniapi;

public final class RoadToSystem {

    private static final RoadToSystem instance = new RoadToSystem();

    private RoadToSystem() {
    }

    public static RoadToSystem getInstance() {
        return instance;
    }

    public native int linkSystemLib();

    static {
        System.loadLibrary("roadtosystem");
    }
}
