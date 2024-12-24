QT += qml quick serialport positioning serialbus
CONFIG += c++17 qtquickcompiler staticlib

QMAKE_CXXFLAGS += -Werror

TARGET = VolvoDigitalDashModels
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += src/main.cpp \
    src/config/can_frame_config.cpp \
    src/config/config.cpp \
    src/dash/dash.cpp \
    src/dash/dash_lights.cpp \
    src/gauge/gauge_accessory.cpp \
    src/ll/adc.cpp \
    src/ll/mcp23017.cpp \
    src/ll/pulse_counter.cpp \
    src/ll/pwm.cpp \
    src/model/accessory_gauge_model.cpp \
    src/model/indicator_model.cpp \
    src/model/odometer_model.cpp \
    src/model/speedometer_model.cpp \
    src/model/tachometer_model.cpp \
    src/model/temp_and_fuel_gauge_model.cpp \
    src/model/warning_light_model.cpp \
    src/sensor/ntc.cpp \
    src/sensor/analog_12v_input.cpp \
    src/sensor/map_sensor.cpp \
    src/sensor_source/sensor_source_gps.cpp \
    src/utils/backlight_control.cpp \
    src/utils/event_timers.cpp \
    src/utils/sensor_utils.cpp \
    src/utils/units.cpp


RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../../eigen/Eigen/Cholesky \
    ../../eigen/Eigen/CholmodSupport \
    ../../eigen/Eigen/Core \
    ../../eigen/Eigen/Dense \
    ../../eigen/Eigen/Eigen \
    ../../eigen/Eigen/Eigenvalues \
    ../../eigen/Eigen/Geometry \
    ../../eigen/Eigen/Householder \
    ../../eigen/Eigen/IterativeLinearSolvers \
    ../../eigen/Eigen/Jacobi \
    ../../eigen/Eigen/KLUSupport \
    ../../eigen/Eigen/LU \
    ../../eigen/Eigen/MetisSupport \
    ../../eigen/Eigen/OrderingMethods \
    ../../eigen/Eigen/PaStiXSupport \
    ../../eigen/Eigen/PardisoSupport \
    ../../eigen/Eigen/QR \
    ../../eigen/Eigen/QtAlignedMalloc \
    ../../eigen/Eigen/SPQRSupport \
    ../../eigen/Eigen/SVD \
    ../../eigen/Eigen/Sparse \
    ../../eigen/Eigen/SparseCholesky \
    ../../eigen/Eigen/SparseCore \
    ../../eigen/Eigen/SparseLU \
    ../../eigen/Eigen/SparseQR \
    ../../eigen/Eigen/StdDeque \
    ../../eigen/Eigen/StdList \
    ../../eigen/Eigen/StdVector \
    ../../eigen/Eigen/SuperLUSupport \
    ../../eigen/Eigen/UmfPackSupport \
    ../../eigen/Eigen/src/Cholesky/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/Cholesky/LDLT.h \
    ../../eigen/Eigen/src/Cholesky/LLT.h \
    ../../eigen/Eigen/src/Cholesky/LLT_LAPACKE.h \
    ../../eigen/Eigen/src/CholmodSupport/CholmodSupport.h \
    ../../eigen/Eigen/src/CholmodSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/Core/ArithmeticSequence.h \
    ../../eigen/Eigen/src/Core/Array.h \
    ../../eigen/Eigen/src/Core/ArrayBase.h \
    ../../eigen/Eigen/src/Core/ArrayWrapper.h \
    ../../eigen/Eigen/src/Core/Assign.h \
    ../../eigen/Eigen/src/Core/AssignEvaluator.h \
    ../../eigen/Eigen/src/Core/Assign_MKL.h \
    ../../eigen/Eigen/src/Core/BandMatrix.h \
    ../../eigen/Eigen/src/Core/Block.h \
    ../../eigen/Eigen/src/Core/BooleanRedux.h \
    ../../eigen/Eigen/src/Core/CommaInitializer.h \
    ../../eigen/Eigen/src/Core/ConditionEstimator.h \
    ../../eigen/Eigen/src/Core/CoreEvaluators.h \
    ../../eigen/Eigen/src/Core/CoreIterators.h \
    ../../eigen/Eigen/src/Core/CwiseBinaryOp.h \
    ../../eigen/Eigen/src/Core/CwiseNullaryOp.h \
    ../../eigen/Eigen/src/Core/CwiseTernaryOp.h \
    ../../eigen/Eigen/src/Core/CwiseUnaryOp.h \
    ../../eigen/Eigen/src/Core/CwiseUnaryView.h \
    ../../eigen/Eigen/src/Core/DenseBase.h \
    ../../eigen/Eigen/src/Core/DenseCoeffsBase.h \
    ../../eigen/Eigen/src/Core/DenseStorage.h \
    ../../eigen/Eigen/src/Core/Diagonal.h \
    ../../eigen/Eigen/src/Core/DiagonalMatrix.h \
    ../../eigen/Eigen/src/Core/DiagonalProduct.h \
    ../../eigen/Eigen/src/Core/Dot.h \
    ../../eigen/Eigen/src/Core/EigenBase.h \
    ../../eigen/Eigen/src/Core/ForceAlignedAccess.h \
    ../../eigen/Eigen/src/Core/Fuzzy.h \
    ../../eigen/Eigen/src/Core/GeneralProduct.h \
    ../../eigen/Eigen/src/Core/GenericPacketMath.h \
    ../../eigen/Eigen/src/Core/GlobalFunctions.h \
    ../../eigen/Eigen/src/Core/IO.h \
    ../../eigen/Eigen/src/Core/IndexedView.h \
    ../../eigen/Eigen/src/Core/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/Core/Inverse.h \
    ../../eigen/Eigen/src/Core/Map.h \
    ../../eigen/Eigen/src/Core/MapBase.h \
    ../../eigen/Eigen/src/Core/MathFunctions.h \
    ../../eigen/Eigen/src/Core/MathFunctionsImpl.h \
    ../../eigen/Eigen/src/Core/Matrix.h \
    ../../eigen/Eigen/src/Core/MatrixBase.h \
    ../../eigen/Eigen/src/Core/NestByValue.h \
    ../../eigen/Eigen/src/Core/NoAlias.h \
    ../../eigen/Eigen/src/Core/NumTraits.h \
    ../../eigen/Eigen/src/Core/PartialReduxEvaluator.h \
    ../../eigen/Eigen/src/Core/PermutationMatrix.h \
    ../../eigen/Eigen/src/Core/PlainObjectBase.h \
    ../../eigen/Eigen/src/Core/Product.h \
    ../../eigen/Eigen/src/Core/ProductEvaluators.h \
    ../../eigen/Eigen/src/Core/Random.h \
    ../../eigen/Eigen/src/Core/Redux.h \
    ../../eigen/Eigen/src/Core/Ref.h \
    ../../eigen/Eigen/src/Core/Replicate.h \
    ../../eigen/Eigen/src/Core/Reshaped.h \
    ../../eigen/Eigen/src/Core/ReturnByValue.h \
    ../../eigen/Eigen/src/Core/Reverse.h \
    ../../eigen/Eigen/src/Core/Select.h \
    ../../eigen/Eigen/src/Core/SelfAdjointView.h \
    ../../eigen/Eigen/src/Core/SelfCwiseBinaryOp.h \
    ../../eigen/Eigen/src/Core/Solve.h \
    ../../eigen/Eigen/src/Core/SolveTriangular.h \
    ../../eigen/Eigen/src/Core/SolverBase.h \
    ../../eigen/Eigen/src/Core/StableNorm.h \
    ../../eigen/Eigen/src/Core/StlIterators.h \
    ../../eigen/Eigen/src/Core/Stride.h \
    ../../eigen/Eigen/src/Core/Swap.h \
    ../../eigen/Eigen/src/Core/Transpose.h \
    ../../eigen/Eigen/src/Core/Transpositions.h \
    ../../eigen/Eigen/src/Core/TriangularMatrix.h \
    ../../eigen/Eigen/src/Core/VectorBlock.h \
    ../../eigen/Eigen/src/Core/VectorwiseOp.h \
    ../../eigen/Eigen/src/Core/Visitor.h \
    ../../eigen/Eigen/src/Core/arch/AVX/Complex.h \
    ../../eigen/Eigen/src/Core/arch/AVX/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/AVX/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/AVX/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/AVX512/Complex.h \
    ../../eigen/Eigen/src/Core/arch/AVX512/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/AVX512/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/AVX512/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/Complex.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/MatrixProduct.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/MatrixProductCommon.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/MatrixProductMMA.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/MatrixVectorProduct.h \
    ../../eigen/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/Default/BFloat16.h \
    ../../eigen/Eigen/src/Core/arch/Default/ConjHelper.h \
    ../../eigen/Eigen/src/Core/arch/Default/GenericPacketMathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/Default/GenericPacketMathFunctionsFwd.h \
    ../../eigen/Eigen/src/Core/arch/Default/Half.h \
    ../../eigen/Eigen/src/Core/arch/Default/Settings.h \
    ../../eigen/Eigen/src/Core/arch/Default/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/GPU/Complex.h \
    ../../eigen/Eigen/src/Core/arch/GPU/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/GPU/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/GPU/Tuple.h \
    ../../eigen/Eigen/src/Core/arch/GPU/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/HIP/hcc/math_constants.h \
    ../../eigen/Eigen/src/Core/arch/MSA/Complex.h \
    ../../eigen/Eigen/src/Core/arch/MSA/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/MSA/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/NEON/Complex.h \
    ../../eigen/Eigen/src/Core/arch/NEON/GeneralBlockPanelKernel.h \
    ../../eigen/Eigen/src/Core/arch/NEON/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/NEON/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/NEON/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/NEON/UnaryFunctors.h \
    ../../eigen/Eigen/src/Core/arch/SSE/Complex.h \
    ../../eigen/Eigen/src/Core/arch/SSE/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/SSE/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/SSE/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/SVE/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/SVE/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/SVE/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/SYCL/InteropHeaders.h \
    ../../eigen/Eigen/src/Core/arch/SYCL/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/SYCL/PacketMath.h \
    ../../eigen/Eigen/src/Core/arch/SYCL/SyclMemoryModel.h \
    ../../eigen/Eigen/src/Core/arch/SYCL/TypeCasting.h \
    ../../eigen/Eigen/src/Core/arch/ZVector/Complex.h \
    ../../eigen/Eigen/src/Core/arch/ZVector/MathFunctions.h \
    ../../eigen/Eigen/src/Core/arch/ZVector/PacketMath.h \
    ../../eigen/Eigen/src/Core/functors/AssignmentFunctors.h \
    ../../eigen/Eigen/src/Core/functors/BinaryFunctors.h \
    ../../eigen/Eigen/src/Core/functors/NullaryFunctors.h \
    ../../eigen/Eigen/src/Core/functors/StlFunctors.h \
    ../../eigen/Eigen/src/Core/functors/TernaryFunctors.h \
    ../../eigen/Eigen/src/Core/functors/UnaryFunctors.h \
    ../../eigen/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    ../../eigen/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    ../../eigen/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    ../../eigen/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h \
    ../../eigen/Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
    ../../eigen/Eigen/src/Core/products/GeneralMatrixVector.h \
    ../../eigen/Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
    ../../eigen/Eigen/src/Core/products/Parallelizer.h \
    ../../eigen/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    ../../eigen/Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
    ../../eigen/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    ../../eigen/Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
    ../../eigen/Eigen/src/Core/products/SelfadjointProduct.h \
    ../../eigen/Eigen/src/Core/products/SelfadjointRank2Update.h \
    ../../eigen/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    ../../eigen/Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
    ../../eigen/Eigen/src/Core/products/TriangularMatrixVector.h \
    ../../eigen/Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
    ../../eigen/Eigen/src/Core/products/TriangularSolverMatrix.h \
    ../../eigen/Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
    ../../eigen/Eigen/src/Core/products/TriangularSolverVector.h \
    ../../eigen/Eigen/src/Core/util/BlasUtil.h \
    ../../eigen/Eigen/src/Core/util/ConfigureVectorization.h \
    ../../eigen/Eigen/src/Core/util/Constants.h \
    ../../eigen/Eigen/src/Core/util/DisableStupidWarnings.h \
    ../../eigen/Eigen/src/Core/util/ForwardDeclarations.h \
    ../../eigen/Eigen/src/Core/util/IndexedViewHelper.h \
    ../../eigen/Eigen/src/Core/util/IntegralConstant.h \
    ../../eigen/Eigen/src/Core/util/MKL_support.h \
    ../../eigen/Eigen/src/Core/util/Macros.h \
    ../../eigen/Eigen/src/Core/util/Memory.h \
    ../../eigen/Eigen/src/Core/util/Meta.h \
    ../../eigen/Eigen/src/Core/util/NonMPL2.h \
    ../../eigen/Eigen/src/Core/util/ReenableStupidWarnings.h \
    ../../eigen/Eigen/src/Core/util/ReshapedHelper.h \
    ../../eigen/Eigen/src/Core/util/Serializer.h \
    ../../eigen/Eigen/src/Core/util/StaticAssert.h \
    ../../eigen/Eigen/src/Core/util/SymbolicIndex.h \
    ../../eigen/Eigen/src/Core/util/XprHelper.h \
    ../../eigen/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    ../../eigen/Eigen/src/Eigenvalues/ComplexSchur.h \
    ../../eigen/Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
    ../../eigen/Eigen/src/Eigenvalues/EigenSolver.h \
    ../../eigen/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    ../../eigen/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    ../../eigen/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    ../../eigen/Eigen/src/Eigenvalues/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    ../../eigen/Eigen/src/Eigenvalues/RealQZ.h \
    ../../eigen/Eigen/src/Eigenvalues/RealSchur.h \
    ../../eigen/Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
    ../../eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    ../../eigen/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
    ../../eigen/Eigen/src/Eigenvalues/Tridiagonalization.h \
    ../../eigen/Eigen/src/Geometry/AlignedBox.h \
    ../../eigen/Eigen/src/Geometry/AngleAxis.h \
    ../../eigen/Eigen/src/Geometry/EulerAngles.h \
    ../../eigen/Eigen/src/Geometry/Homogeneous.h \
    ../../eigen/Eigen/src/Geometry/Hyperplane.h \
    ../../eigen/Eigen/src/Geometry/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/Geometry/OrthoMethods.h \
    ../../eigen/Eigen/src/Geometry/ParametrizedLine.h \
    ../../eigen/Eigen/src/Geometry/Quaternion.h \
    ../../eigen/Eigen/src/Geometry/Rotation2D.h \
    ../../eigen/Eigen/src/Geometry/RotationBase.h \
    ../../eigen/Eigen/src/Geometry/Scaling.h \
    ../../eigen/Eigen/src/Geometry/Transform.h \
    ../../eigen/Eigen/src/Geometry/Translation.h \
    ../../eigen/Eigen/src/Geometry/Umeyama.h \
    ../../eigen/Eigen/src/Geometry/arch/Geometry_SIMD.h \
    ../../eigen/Eigen/src/Householder/BlockHouseholder.h \
    ../../eigen/Eigen/src/Householder/Householder.h \
    ../../eigen/Eigen/src/Householder/HouseholderSequence.h \
    ../../eigen/Eigen/src/Householder/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
    ../../eigen/Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
    ../../eigen/Eigen/src/Jacobi/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/Jacobi/Jacobi.h \
    ../../eigen/Eigen/src/KLUSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/KLUSupport/KLUSupport.h \
    ../../eigen/Eigen/src/LU/Determinant.h \
    ../../eigen/Eigen/src/LU/FullPivLU.h \
    ../../eigen/Eigen/src/LU/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/LU/InverseImpl.h \
    ../../eigen/Eigen/src/LU/PartialPivLU.h \
    ../../eigen/Eigen/src/LU/PartialPivLU_LAPACKE.h \
    ../../eigen/Eigen/src/LU/arch/InverseSize4.h \
    ../../eigen/Eigen/src/MetisSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/MetisSupport/MetisSupport.h \
    ../../eigen/Eigen/src/OrderingMethods/Amd.h \
    ../../eigen/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    ../../eigen/Eigen/src/OrderingMethods/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/OrderingMethods/Ordering.h \
    ../../eigen/Eigen/src/PaStiXSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    ../../eigen/Eigen/src/PardisoSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/PardisoSupport/PardisoSupport.h \
    ../../eigen/Eigen/src/QR/ColPivHouseholderQR.h \
    ../../eigen/Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
    ../../eigen/Eigen/src/QR/CompleteOrthogonalDecomposition.h \
    ../../eigen/Eigen/src/QR/FullPivHouseholderQR.h \
    ../../eigen/Eigen/src/QR/HouseholderQR.h \
    ../../eigen/Eigen/src/QR/HouseholderQR_LAPACKE.h \
    ../../eigen/Eigen/src/QR/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SPQRSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    ../../eigen/Eigen/src/SVD/BDCSVD.h \
    ../../eigen/Eigen/src/SVD/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SVD/JacobiSVD.h \
    ../../eigen/Eigen/src/SVD/JacobiSVD_LAPACKE.h \
    ../../eigen/Eigen/src/SVD/SVDBase.h \
    ../../eigen/Eigen/src/SVD/UpperBidiagonalization.h \
    ../../eigen/Eigen/src/SparseCholesky/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    ../../eigen/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    ../../eigen/Eigen/src/SparseCore/AmbiVector.h \
    ../../eigen/Eigen/src/SparseCore/CompressedStorage.h \
    ../../eigen/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    ../../eigen/Eigen/src/SparseCore/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SparseCore/SparseAssign.h \
    ../../eigen/Eigen/src/SparseCore/SparseBlock.h \
    ../../eigen/Eigen/src/SparseCore/SparseColEtree.h \
    ../../eigen/Eigen/src/SparseCore/SparseCompressedBase.h \
    ../../eigen/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    ../../eigen/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    ../../eigen/Eigen/src/SparseCore/SparseDenseProduct.h \
    ../../eigen/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    ../../eigen/Eigen/src/SparseCore/SparseDot.h \
    ../../eigen/Eigen/src/SparseCore/SparseFuzzy.h \
    ../../eigen/Eigen/src/SparseCore/SparseMap.h \
    ../../eigen/Eigen/src/SparseCore/SparseMatrix.h \
    ../../eigen/Eigen/src/SparseCore/SparseMatrixBase.h \
    ../../eigen/Eigen/src/SparseCore/SparsePermutation.h \
    ../../eigen/Eigen/src/SparseCore/SparseProduct.h \
    ../../eigen/Eigen/src/SparseCore/SparseRedux.h \
    ../../eigen/Eigen/src/SparseCore/SparseRef.h \
    ../../eigen/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    ../../eigen/Eigen/src/SparseCore/SparseSolverBase.h \
    ../../eigen/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    ../../eigen/Eigen/src/SparseCore/SparseTranspose.h \
    ../../eigen/Eigen/src/SparseCore/SparseTriangularView.h \
    ../../eigen/Eigen/src/SparseCore/SparseUtil.h \
    ../../eigen/Eigen/src/SparseCore/SparseVector.h \
    ../../eigen/Eigen/src/SparseCore/SparseView.h \
    ../../eigen/Eigen/src/SparseCore/TriangularSolver.h \
    ../../eigen/Eigen/src/SparseLU/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU.h \
    ../../eigen/Eigen/src/SparseLU/SparseLUImpl.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_Memory.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_Structs.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_Utils.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_pivotL.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_pruneL.h \
    ../../eigen/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    ../../eigen/Eigen/src/SparseQR/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SparseQR/SparseQR.h \
    ../../eigen/Eigen/src/StlSupport/StdDeque.h \
    ../../eigen/Eigen/src/StlSupport/StdList.h \
    ../../eigen/Eigen/src/StlSupport/StdVector.h \
    ../../eigen/Eigen/src/StlSupport/details.h \
    ../../eigen/Eigen/src/SuperLUSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    ../../eigen/Eigen/src/UmfPackSupport/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/UmfPackSupport/UmfPackSupport.h \
    ../../eigen/Eigen/src/misc/Image.h \
    ../../eigen/Eigen/src/misc/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/misc/Kernel.h \
    ../../eigen/Eigen/src/misc/RealSvd2x2.h \
    ../../eigen/Eigen/src/misc/blas.h \
    ../../eigen/Eigen/src/misc/lapack.h \
    ../../eigen/Eigen/src/misc/lapacke.h \
    ../../eigen/Eigen/src/misc/lapacke_helpers.h \
    ../../eigen/Eigen/src/misc/lapacke_mangling.h \
    ../../eigen/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    ../../eigen/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    ../../eigen/Eigen/src/plugins/BlockMethods.h \
    ../../eigen/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    ../../eigen/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    ../../eigen/Eigen/src/plugins/IndexedViewMethods.h \
    ../../eigen/Eigen/src/plugins/InternalHeaderCheck.h \
    ../../eigen/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    ../../eigen/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    ../../eigen/Eigen/src/plugins/ReshapedMethods.h \
    inc/config/can_frame_config.h \
    inc/config/config.h \
    inc/config/config_keys.h \
    inc/config/gauge_configs.h \
    inc/config/sensor_configs.h \
    inc/dash/dash.h \
    inc/dash/dash_host.h \
    inc/dash/dash_lights.h \
    inc/gauge/gauge.h \
    inc/gauge/gauge_accessory.h \
    inc/gauge/gauge_odo.h \
    inc/gauge/gauge_speedo.h \
    inc/gauge/gauge_tach.h \
    inc/gauge/gauge_temp_fuel_cluster.h \
    inc/ll/adc.h \
    inc/ll/mcp23017.h \
    inc/ll/pulse_counter.h \
    inc/ll/pwm.h \
    inc/ll/tach_input.h \
    inc/ll/vss_input.h \
    inc/model/accessory_gauge_model.h \
    inc/model/indicator_model.h \
    inc/model/odometer_model.h \
    inc/model/speedometer_model.h \
    inc/model/tachometer_model.h \
    inc/model/temp_and_fuel_gauge_model.h \
    inc/model/warning_light_model.h \
    inc/sensor/analog_12v_input.h \
    inc/sensor/map_sensor.h \
    inc/sensor/ntc.h \
    inc/sensor/sensor.h \
    inc/sensor/sensor_can.h \
    inc/sensor/sensor_map.h \
    inc/sensor/sensor_ntc.h \
    inc/sensor/sensor_odometer.h \
    inc/sensor/sensor_resistive.h \
    inc/sensor/sensor_speedo.h \
    inc/sensor/sensor_tach.h \
    inc/sensor/sensor_voltmeter.h \
    inc/sensor_source/sensor_source.h \
    inc/sensor_source/sensor_source_adc.h \
    inc/sensor_source/sensor_source_can.h \
    inc/sensor_source/sensor_source_gpio.h \
    inc/sensor_source/sensor_source_gps.h \
    inc/sensor_source/sensor_source_tach.h \
    inc/sensor_source/sensor_source_vss.h \
    inc/utils/backlight_control.h \
    inc/utils/event_timers.h \
    inc/utils/gps_helper.h \
    inc/utils/key_press_emitter.h \
    inc/utils/sensor_utils.h \
    inc/utils/units.h


INCLUDEPATH += \
    Headers \
    inc \
    inc/config \
    inc/dash \
    inc/gauge \
    inc/ll \
    inc/model \
    inc/sensor \
    inc/sensor_source \
    inc/utils \

RPI {
    message("rpi is selected")
    DEFINES += RASPBERRY_PI
}

DISTFILES +=
