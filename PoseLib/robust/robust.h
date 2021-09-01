#ifndef POSELIB_ROBUST_H_
#define POSELIB_ROBUST_H_

#include "bundle.h"
#include "colmap_models.h"
#include "ransac.h"
#include "types.h"
#include <PoseLib/types.h>
#include <vector>

namespace pose_lib {

// Estimates absolute pose using LO-RANSAC followed by non-linear refinement
RansacStats estimate_absolute_pose(const std::vector<Eigen::Vector2d> &points2D,
                                   const std::vector<Eigen::Vector3d> &points3D,
                                   const Camera &camera, const RansacOptions &ransac_opt,
                                   const BundleOptions &bundle_opt,
                                   CameraPose *pose, std::vector<char> *inliers);

// Estimates generalized absolute pose using LO-RANSAC followed by non-linear refinement
RansacStats estimate_generalized_absolute_pose(
    const std::vector<std::vector<Eigen::Vector2d>> &points2D,
    const std::vector<std::vector<Eigen::Vector3d>> &points3D,
    const std::vector<CameraPose> &camera_ext,
    const std::vector<Camera> &cameras,
    const RansacOptions &ransac_opt,
    const BundleOptions &bundle_opt,
    CameraPose *pose, std::vector<std::vector<char>> *inliers);

// Estimates relative pose using LO-RANSAC followed by non-linear refinement
RansacStats estimate_relative_pose(
    const std::vector<Eigen::Vector2d> &points2D_1,
    const std::vector<Eigen::Vector2d> &points2D_2,
    const Camera &camera1, const Camera &camera2,
    const RansacOptions &ransac_opt, const BundleOptions &bundle_opt,
    CameraPose *relative_pose, std::vector<char> *inliers);

// Estimates generalized relative pose using LO-RANSAC followed by non-linear refinement
RansacStats estimate_generalized_relative_pose(
    const std::vector<PairwiseMatches> &matches,
    const std::vector<CameraPose> &camera1_ext,
    const std::vector<Camera> &cameras1,
    const std::vector<CameraPose> &camera2_ext,
    const std::vector<Camera> &cameras2,
    const RansacOptions &ransac_opt, const BundleOptions &bundle_opt,
    CameraPose *relative_pose, std::vector<std::vector<char>> *inliers);

// Estimates camera pose from hybrid correspondences using LO-RANSAC followed by non-linear refinement
//  camera are the intrinsics for the query camera
//  (points2D, points3D) are the 2D-3D matches
//  (matches2D_2D, map_ext, map_cameras) are the 2D-2D matches to the map images with extrinsics/intrinsics
//     Note for matches2D_2D it is assumed that cam_ind1 indexes into map_cameras and map_ext, and cam_ind2 = 0
//     So that PairwiseMatches::x1 are the map image 2D points and PairwiseMatches::x2 are in the query camera
// TODO: Not fully implemented (only p3p sampling for now) and very untested!
RansacStats estimate_hybrid_pose(const std::vector<Eigen::Vector2d> &points2D,
                                 const std::vector<Eigen::Vector3d> &points3D,
                                 const std::vector<PairwiseMatches> &matches2D_2D,
                                 const Camera &camera,
                                 const std::vector<CameraPose> &map_ext, const std::vector<Camera> &map_cameras,
                                 const RansacOptions &ransac_opt, const BundleOptions &bundle_opt,
                                 CameraPose *pose, std::vector<char> *inliers_2D_3D,
                                 std::vector<std::vector<char>> *inliers_2D_2D);

// Estimates generalized camera pose from hybrid correspondences using LO-RANSAC followed by non-linear refinement
//  (points2D_1, points3D_1) are the 2D-3D matches where the 2D point is in the first rig and the 3D points are in the second
//  (points2D_2, points3D_2) are the 2D-3D matches where the 2D point is in the second rig and the 3D points are in the first
//  (matches2D_2D) are the 2D-2D matches between the generalized cameras
//  camerasX, cameraX_ext  are the intrinsics/extrinsics for each of the generalized cameras
// TODO: Not yet implemented.
RansacStats estimate_generalized_hybrid_pose(
    const std::vector<std::vector<Eigen::Vector2d>> &points2D_1,
    const std::vector<std::vector<Eigen::Vector3d>> &points3D_1,
    const std::vector<std::vector<Eigen::Vector2d>> &points2D_2,
    const std::vector<std::vector<Eigen::Vector3d>> &points3D_2,
    const std::vector<PairwiseMatches> &matches2D_2D,
    const std::vector<CameraPose> &camera1_ext, const std::vector<Camera> &cameras1,
    const std::vector<CameraPose> &camera2_ext, const std::vector<Camera> &cameras2,
    const RansacOptions &ransac_opt, const BundleOptions &bundle_opt,
    CameraPose *pose,
    std::vector<std::vector<char>> *inliers_1,
    std::vector<std::vector<char>> *inliers_2,
    std::vector<std::vector<char>> *inliers_2D_2D);

} // namespace pose_lib

#endif