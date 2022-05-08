/*
 * Copyright (C) 2021 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2021 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugin-fw
 * Created on: 20 июл. 2021 г.
 *
 * lsp-plugin-fw is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugin-fw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugin-fw. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef LSP_PLUG_IN_PLUG_FW_CTL_SPECIFIC_AUDIOSAMPLE_H_
#define LSP_PLUG_IN_PLUG_FW_CTL_SPECIFIC_AUDIOSAMPLE_H_

#ifndef LSP_PLUG_IN_PLUG_FW_CTL_IMPL_
    #error "Use #include <lsp-plug.in/plug-fw/ctl.h>"
#endif /* LSP_PLUG_IN_PLUG_FW_CTL_IMPL_ */

#include <lsp-plug.in/plug-fw/version.h>
#include <lsp-plug.in/tk/tk.h>

namespace lsp
{
    namespace ctl
    {
        /**
         * Rack widget controller
         */
        class AudioSample: public Widget
        {
            public:
                static const ctl_class_t metadata;

            protected:
                enum labels_t
                {
                    LBL_FILE_NAME,
                    LBL_DURATION,
                    LBL_HEAD_CUT,
                    LBL_TAIL_CUT,
                    LBL_MISC,

                    LBL_COUNT
                };

            protected:
                class DataSink: public tk::TextDataSink
                {
                    private:
                        AudioSample    *pSample;

                    public:
                        explicit DataSink(AudioSample *sample);
                        virtual ~DataSink();

                    public:
                        virtual status_t    receive(const LSPString *text, const char *mime);
                        virtual status_t    error(status_t code);

                        void        unbind();
                };

                class DragInSink: public tk::URLSink
                {
                    protected:
                        AudioSample    *pSample;

                    public:
                        explicit DragInSink(AudioSample *sample);
                        virtual ~DragInSink();

                        void unbind();
                        virtual status_t    commit_url(const LSPString *url);
                };

            protected:
                ui::IPort          *pPort;
                ui::IPort          *pMeshPort;
                ui::IPort          *pPathPort;
                tk::FileDialog     *pDialog;
                tk::Menu           *pMenu;
                DataSink           *pDataSink;
                DragInSink         *pDragInSink;
                lltl::parray<file_format_t>     vFormats;
                lltl::parray<tk::MenuItem>      vMenuItems;
                lltl::pphash<char, ui::IPort>   vClipboardBind;

                ctl::Integer        sWaveBorder;
                ctl::Integer        sFadeInBorder;
                ctl::Integer        sFadeOutBorder;
                ctl::Integer        sLineWidth;
                ctl::LCString       sMainText;
                ctl::Integer        sLabelRadius;
                ctl::Integer        sBorder;
                ctl::Integer        sBorderRadius;
                ctl::Boolean        sActive;
                ctl::Boolean        sStereoGroups;
                ctl::Boolean        sLabelVisibility[tk::AudioSample::LABELS];
                ctl::Boolean        sBorderFlat;
                ctl::Boolean        sGlass;

                ctl::Expression     sStatus;
                ctl::Expression     sSampleRate;
                ctl::Expression     sHeadCut;
                ctl::Expression     sTailCut;
                ctl::Expression     sFadeIn;
                ctl::Expression     sFadeOut;
                ctl::Expression     sLength;

                ctl::Padding        sIPadding;

                ctl::Color          sColor;
                ctl::Color          sBorderColor;
                ctl::Color          sGlassColor;
                ctl::Color          sLineColor;
                ctl::Color          sMainColor;
                ctl::Color          sLabelTextColor[tk::AudioSample::LABELS];
                ctl::Color          sLabelBgColor;

            protected:
                static status_t     slot_audio_sample_submit(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_dialog_submit(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_dialog_hide(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_popup_cut_action(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_popup_copy_action(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_popup_paste_action(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_popup_clear_action(tk::Widget *sender, void *ptr, void *data);
                static status_t     slot_drag_request(tk::Widget *sender, void *ptr, void *data);

            protected:
                void                show_file_dialog();
                void                update_path();
                void                commit_file();
                void                sync_status();
                void                sync_labels();
                void                sync_mesh();
                tk::Menu           *create_menu();
                tk::MenuItem       *create_menu_item(tk::Menu *menu);

            public:
                explicit AudioSample(ui::IWrapper *wrapper, tk::AudioSample *widget);
                virtual ~AudioSample();

                virtual status_t    init();

            public:
                virtual void        set(ui::UIContext *ctx, const char *name, const char *value);
                virtual void        end(ui::UIContext *ctx);
                virtual void        notify(ui::IPort *port);
                virtual void        reloaded(const tk::StyleSheet *sheet);
        };

    } /* namespace ctl */
} /* namespace lsp */



#endif /* LSP_PLUG_IN_PLUG_FW_CTL_SPECIFIC_AUDIOSAMPLE_H_ */
