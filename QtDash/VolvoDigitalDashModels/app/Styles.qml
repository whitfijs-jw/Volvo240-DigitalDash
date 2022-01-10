import QtQuick 2.7
pragma Singleton

QtObject {

    property QtObject colors: QtObject {
        property color blue: "#56baca";
        property color yellow: "#caa856";
        property color green: "#56ca8a";
        property color red: "#ed4545";
        property color white: "#ffffff";
        property color lightGray: "#e7edf3";
        property color mediumGray: "#868f99";
        property color darkGray: "#4c555f";
        property color darkBlue: "#496077";
        property color nearBlack: "#191e24";
        property color black: "black";
    }

    property Gradient buttonGradient:
        Gradient {
            GradientStop { position: 0.0; color: colors.darkGray }
            GradientStop { position: 1.0; color: "#394148" }
        }

    property Gradient needleCenterGradient:
        Gradient {
            GradientStop { position: 0.0; color: colors.black}
            GradientStop { position: 0.5; color: colors.darkGray }
            GradientStop { position: 1.0; color: colors.black }
        }

    property Gradient needle240Gradient: Gradient {
                GradientStop { position: 0.25; color: "orange"}
                GradientStop { position: 0.5; color: "white" }
                GradientStop { position: 0.75; color: "orange" }
    }

}
