# Copyright (c) 2019-2021 Nordic Semiconductor ASA
# Copyright 2026 NXP
# SPDX-License-Identifier: BSD-3-Clause
#
# Zephyr docset build configuration.
# Imports upstream Zephyr conf.py and overrides for NXP theming.

import json
import os
import sys
from pathlib import Path

from sphinx.config import eval_config_file

# -- Paths ---------------------------------------------------------------------

ZSDK_BASE = Path(__file__).absolute().parents[2]

sys.path.insert(0, str(ZSDK_BASE / "doc" / "scripts" / "_utils"))
import utils  # noqa: E402

ZEPHYR_BASE = utils.get_projdir("zephyr")

# pylint: disable=undefined-variable,used-before-assignment

# -- Import upstream Zephyr configuration --------------------------------------

os.environ["ZEPHYR_BASE"] = str(ZEPHYR_BASE)
os.environ["OUTPUT_DIR"] = str(utils.get_builddir() / "html" / "zephyr")

_zephyr_conf_path = ZEPHYR_BASE / "doc" / "conf.py"
try:
    conf = eval_config_file(_zephyr_conf_path, tags)
except TypeError:
    conf = eval_config_file(str(_zephyr_conf_path), tags)
locals().update(conf)

sys.path.insert(0, str(ZSDK_BASE / "doc" / "_extensions"))

# -- Extensions ----------------------------------------------------------------

extensions.remove("sphinx_sitemap")
extensions = [
    "sphinx.ext.intersphinx",
    "mcux_book_theme.extensions.toc_builder",
] + extensions

# -- Cross-docset TOC builder --------------------------------------------------

toc_builder_docsets = [
    {
        "docset": "zsdk",
        "title": "NXP Zephyr Project",
        "doc_root": str(ZSDK_BASE / "doc"),
        "index_file": str(ZSDK_BASE / "doc" / "index.rst"),
    },
    {
        "docset": "zephyr",
        "title": "Zephyr Project",
        "doc_root": str(ZEPHYR_BASE / "doc"),
        "index_file": str(ZEPHYR_BASE / "doc" / "index.rst"),
        "content_root": str(ZEPHYR_BASE),
    },
]

# -- HTML output ---------------------------------------------------------------

html_theme = "mcux_book_theme"
html_title = "Zephyr Project documentation (NXP)"
html_last_updated_fmt = "%b %d, %Y"

html_theme_options = {
    "repository_url": "https://github.com/nxp-zephyr/nxp-zephyr",
    "show_toc_level": 2,
    "collapse_navigation": True,
    "navigation_depth": 3,
    "enable_cross_docset_nav": True,
}

templates_path = []
html_static_path = [str(ZSDK_BASE / "doc" / "_static")]
html_css_files = []

with open(ZSDK_BASE / "doc" / "versions.json", "r", encoding="utf-8") as f:
    versions_data = json.load(f)

version_url_template = os.environ.get(
    "DOCS_VERSION_URL_TEMPLATE", "/zsdk/{version}/html/zephyr"
)
version_list = [
    (v, version_url_template.format(version=v)) for v in versions_data
]

html_context = {
    "show_license": True,
    "docs_title": html_title,
    "is_release": locals().get("is_release", tags.has("release")),
    "current_docset": "zephyr",
    "docsets": utils.ALL_DOCSETS,
    "current_version": versions_data[0],
    "repository_url": html_theme_options.get("repository_url"),
    "html_title": html_title,
    "versions": tuple(version_list),
}

# -- Zephyr-specific options ---------------------------------------------------

warnings_filter_silent = True

# -- Zephyr gh_utils -----------------------------------------------------------

gh_link_version = "main" if version.endswith("99") else f"v{version}"
gh_link_base_url = "https://github.com/nxp-zephyr/nxp-zsdk"

# pylint: enable=undefined-variable,used-before-assignment


# -- Setup ---------------------------------------------------------------------

def setup(app):
    """Patch ReferencesResolver and pending_xref handlers for Sphinx edge cases."""
    from sphinx.transforms.post_transforms import ReferencesResolver

    original_run = ReferencesResolver.run

    def patched_run(self, **kwargs):
        try:
            original_run(self, **kwargs)
        except ValueError as e:
            if "is not in list" in str(e):
                print(f"Skipping problematic pending_xref resolution: {e}")
            else:
                raise

    ReferencesResolver.run = patched_run

    app.config.suppress_warnings = app.config.suppress_warnings or []
    if "ref.any" not in app.config.suppress_warnings:
        app.config.suppress_warnings.append("ref.any")

    # Fallback handlers for unresolved pending_xref nodes
    def visit_pending_xref(self, node):
        pass

    def depart_pending_xref(self, node):
        pass

    try:
        from sphinx.writers.html5 import HTML5Translator

        if not hasattr(HTML5Translator, "visit_pending_xref"):
            HTML5Translator.visit_pending_xref = visit_pending_xref
            HTML5Translator.depart_pending_xref = depart_pending_xref
    except Exception:
        pass

    return {
        "parallel_read_safe": True,
        "parallel_write_safe": True,
    }
